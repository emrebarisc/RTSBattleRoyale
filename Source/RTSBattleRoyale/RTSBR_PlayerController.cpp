// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSBR_PlayerController.h"

#include "Engine/LocalPlayer.h"

#include "RTSBR_CameraComponent.h"
#include "RTSBR_SpectatorPawn.h"
#include "RTSBR_PlayerCameraManager.h"

ARTSBR_PlayerController::ARTSBR_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bHidden = false;
	bShowMouseCursor = true;

	PlayerCameraManagerClass = ARTSBR_PlayerCameraManager::StaticClass();
}

ARTSBR_SpectatorPawn* ARTSBR_PlayerController::GetMainSpectatorPawn() const
{
	return Cast<ARTSBR_SpectatorPawn>(GetPawn());
}

void ARTSBR_PlayerController::ProcessPlayerInput(const float deltaTime, const bool bGamePaused)
{
	Super::ProcessPlayerInput(deltaTime, bGamePaused);

	{
		const ULocalPlayer* localPlayer = Cast<ULocalPlayer>(Player);
		ARTSBR_SpectatorPawn* spectatorPawn = GetMainSpectatorPawn();

		if (spectatorPawn && localPlayer)
		{
			if (localPlayer->ViewportClient)
			{
				spectatorPawn->GetCameraComponent()->UpdateCameraMovement(this);
			}
		}
	}
}