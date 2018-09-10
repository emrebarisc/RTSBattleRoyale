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

void ARTSBR_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ARTSBR_PlayerController::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ARTSBR_PlayerController::ZoomOut);

	InputComponent->BindAxis("MoveForward", this, &ARTSBR_PlayerController::MovePawnForward);
	InputComponent->BindAxis("MoveRight", this, &ARTSBR_PlayerController::MovePawnRight);
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

void ARTSBR_PlayerController::MovePawnForward(const float value)
{
	ARTSBR_SpectatorPawn *spectatorPawn;
	if (value != 0.f && (spectatorPawn = Cast<ARTSBR_SpectatorPawn>(GetPawn())) != nullptr)
	{
		spectatorPawn->MoveForward(value);
	}
}

void ARTSBR_PlayerController::MovePawnRight(const float value)
{
	ARTSBR_SpectatorPawn *spectatorPawn;
	if (value != 0.f && (spectatorPawn = Cast<ARTSBR_SpectatorPawn>(GetPawn())) != nullptr)
	{
		spectatorPawn->MoveRight(value);
	}
}

void ARTSBR_PlayerController::ZoomIn()
{
	ARTSBR_SpectatorPawn *spectatorPawn;
	if ((spectatorPawn = Cast<ARTSBR_SpectatorPawn>(GetPawn())) != nullptr)
	{
		spectatorPawn->OnMouseScrollUp();
	}
}

void ARTSBR_PlayerController::ZoomOut()
{
	ARTSBR_SpectatorPawn *spectatorPawn;
	if ((spectatorPawn = Cast<ARTSBR_SpectatorPawn>(GetPawn())) != nullptr)
	{
		spectatorPawn->OnMouseScrollDown();
	}
}
