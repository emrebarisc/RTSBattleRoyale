// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSBR_Character.h"

#include "AIController.h"
#include "Components/DecalComponent.h"
#include "ConstructorHelpers.h"

#include "BaseStats.h"
#include "RTSBR_AIController.h"
#include "RTSBR_Character_AnimInstance.h"
#include "Materials/MaterialInstance.h"

ARTSBR_Character::ARTSBR_Character() : 
	damage_(BaseStats::PHYSICAL_DAMAGE, BaseStats::MAGIC_DAMAGE), 
	health_(BaseStats::HEALTH), armor_(BaseStats::ARMOR), magicResistance_(BaseStats::MAGIC_RESISTANCE), 
	attackSpeed_(BaseStats::ATTACK_SPEED), isAttacking_(false)
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> characterSkeletalMeshAsset(TEXT("/Game/Assets/Characters/RTSBR_Character/RTSBR_Character_SkeletalMesh"));
	if (characterSkeletalMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(characterSkeletalMeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));

		static ConstructorHelpers::FClassFinder<URTSBR_Character_AnimInstance> animationBlueprintClass(TEXT("/Game/Blueprints/Characters/Animations/BP_RTSBR_CharacterAnimation"));
		if (animationBlueprintClass.Class)
		{
			GetMesh()->SetAnimInstanceClass(animationBlueprintClass.Class);
		}
	}

	AIControllerClass = ARTSBR_AIController::StaticClass();

	selectionDecalComp_ = CreateDefaultSubobject<UDecalComponent>(TEXT("Selection Decal"));
	selectionDecalComp_->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterial> decalMaterial(TEXT("Material'/Game/Assets/Materials/M_SelectionDecal.M_SelectionDecal'"));
	if(decalMaterial.Succeeded())
	{
		selectionDecalComp_->SetDecalMaterial(decalMaterial.Object);

		selectionDecalComp_->RelativeLocation = FVector(0.f, 0.f, -80.f);
		selectionDecalComp_->DecalSize = FVector(32.f, 64.f, 64.f);
		selectionDecalComp_->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
		selectionDecalComp_->SetVisibility(false);
	}
}

void ARTSBR_Character::BeginPlay()
{
	Super::BeginPlay();
}

void ARTSBR_Character::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void ARTSBR_Character::ApplyDamage(const Damage& damage)
{
	// Calculate damage value with respect to the character's resistance amounts
	health_ -= (damage.physicalDamage * armor_ + damage.magicDamage * magicResistance_) * 0.01f;

	if(health_ <= 0.f)
	{
		Die();
	}
}

void ARTSBR_Character::MoveToDestination(FVector destination)
{
	AController* controller = GetController();
	if (controller)
	{
		ARTSBR_AIController *aiController = Cast<ARTSBR_AIController>(controller);

		if(aiController)
		{
			SetActorRotation(FRotator(0.f, ((destination - GetActorLocation()).GetSafeNormal()).Rotation().Yaw, 0.f));

			aiController->MoveToLocation(destination);

			/*MoveToActor(AActor* Goal, float AcceptanceRadius = -1, bool bStopOnOverlap = true,
				bool bUsePathfinding = true, bool bCanStrafe = true,
				TSubclassOf<UNavigationQueryFilter> FilterClass = NULL, bool bAllowPartialPath = true);*/
			
		}
	}
}

void ARTSBR_Character::SetIsSelected(const bool isSelected) const
{
	selectionDecalComp_->SetVisibility(isSelected);
}

void ARTSBR_Character::Attack()
{

}

float ARTSBR_Character::CalculateDamage()
{
	return 0.f;
}

void ARTSBR_Character::Die()
{
	// Let's destroy the character for now
	Destroy();
}