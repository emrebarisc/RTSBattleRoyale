// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSBR_SpectatorPawn.h"
#include "Components/SphereComponent.h"
#include "Engine/CollisionProfile.h"
#include "Components/InputComponent.h"
#include "RTSBR_CameraComponent.h"

ARTSBR_SpectatorPawn::ARTSBR_SpectatorPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCollisionComponent()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	bAddDefaultMovementBindings = false;

	cameraComponent_ = CreateDefaultSubobject<URTSBR_CameraComponent>(TEXT("Camera Component"));
}

void ARTSBR_SpectatorPawn::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector::ZeroVector);
}

void ARTSBR_SpectatorPawn::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void ARTSBR_SpectatorPawn::SetupPlayerInputComponent(UInputComponent* inputComponent)
{
	check(inputComponent);

	Super::SetupPlayerInputComponent(inputComponent);

	inputComponent->BindAction("ZoomIn", IE_Pressed, this, &ARTSBR_SpectatorPawn::OnMouseScrollUp);
	inputComponent->BindAction("ZoomOut", IE_Pressed, this, &ARTSBR_SpectatorPawn::OnMouseScrollDown);

	inputComponent->BindAxis("MoveForward", this, &ARTSBR_SpectatorPawn::MoveForward);
	inputComponent->BindAxis("MoveRight", this, &ARTSBR_SpectatorPawn::MoveRight);
}

void ARTSBR_SpectatorPawn::MoveForward(const float value)
{
	if(value != 0.f)
	{
		cameraComponent_->MoveForward(value);
	}
}

void ARTSBR_SpectatorPawn::MoveRight(const float value)
{
	if (value != 0.f)
	{
		cameraComponent_->MoveRight(value);
	}
}

void ARTSBR_SpectatorPawn::OnMouseScrollUp()
{
	cameraComponent_->OnZoomIn();
}

void ARTSBR_SpectatorPawn::OnMouseScrollDown()
{
	cameraComponent_->OnZoomOut();
}
