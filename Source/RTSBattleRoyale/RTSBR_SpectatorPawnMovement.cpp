// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSBR_SpectatorPawnMovement.h"
#include "RTSBR_PlayerController.h"
#include "GameFramework/Pawn.h"
#include "RTSBR_SpectatorPawn.h"
#include "RTSBR_CameraComponent.h"


URTSBR_SpectatorPawnMovement::URTSBR_SpectatorPawnMovement()
{
	MaxSpeed = 10000.f;
	Acceleration = 4000.f;
	Deceleration = 4000.f;
}

void URTSBR_SpectatorPawnMovement::TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(deltaTime, tickType, thisTickFunction);

	if(!PawnOwner || !UpdatedComponent)
	{
		return;
	}

	ARTSBR_PlayerController *playerController = Cast<ARTSBR_PlayerController>(PawnOwner->GetController());
	if(playerController && playerController->IsLocalController())
	{
		if(!bInitialLocationSet_)
		{
			bInitialLocationSet_ = true;
			PawnOwner->SetActorRotation(playerController->GetControlRotation());
			PawnOwner->SetActorLocation(playerController->GetSpawnLocation());
		}
	}
}