// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSBR_Character.h"
#include "ConstructorHelpers.h"
#include "RTSBR_Character_AnimInstance.h"
#include "BaseStats.h"

ARTSBR_Character::ARTSBR_Character() : 
	damage_(BaseStats::PHYSICAL_DAMAGE, BaseStats::MAGIC_DAMAGE), 
	health_(BaseStats::HEALTH), armor_(BaseStats::ARMOR), magicResistance_(BaseStats::MAGIC_RESISTANCE), 
	attackSpeed_(BaseStats::ATTACK_SPEED), isAttacking_(false)
{
	PrimaryActorTick.bCanEverTick = true;

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
}

void ARTSBR_Character::BeginPlay()
{
	Super::BeginPlay();
}

void ARTSBR_Character::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	const FVector direction = FVector(1.f, 0.f, 0.f);
	AddMovementInput(direction, 1.f);
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