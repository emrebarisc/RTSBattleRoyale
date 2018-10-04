// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSBR_PlayerController.h"

#include "Engine/LocalPlayer.h"
#include "Components/BoxComponent.h"

#include "RTSBR_CameraComponent.h"
#include "RTSBR_Character.h"
#include "RTSBR_PlayerCameraManager.h"
#include "RTSBR_SpectatorPawn.h"
#include "Engine/Engine.h"

ARTSBR_PlayerController::ARTSBR_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bHidden = false;
	bShowMouseCursor = true;

	PlayerCameraManagerClass = ARTSBR_PlayerCameraManager::StaticClass();

	multipleSelectionBox_ = CreateDefaultSubobject<UBoxComponent>(TEXT("MultipleSelectionBox"));
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

	InputComponent->BindAction("Selection", IE_Pressed, this, &ARTSBR_PlayerController::StartSelection);
	InputComponent->BindAction("Selection", IE_Released, this, &ARTSBR_PlayerController::EndSelection);

	InputComponent->BindAction("Command", IE_Released, this, &ARTSBR_PlayerController::Command);

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

void ARTSBR_PlayerController::StartSelection()
{
	FHitResult hit;
	GetHitResultUnderCursor(ECC_Visibility, false, hit);
	selectionStartPosition_ = hit.Location;
}

void ARTSBR_PlayerController::EndSelection()
{
	FHitResult hit;
	GetHitResultUnderCursor(ECC_Visibility, false, hit);
	selectionEndPosition_ = hit.Location;

	UnitSelection();
}

void ARTSBR_PlayerController::UnitSelection() const
{
	ARTSBR_SpectatorPawn *spectatorPawn;
	if ((spectatorPawn = Cast<ARTSBR_SpectatorPawn>(GetPawn())) == nullptr)
	{
		return;
	}

	FVector extent = FVector((selectionEndPosition_.X - selectionStartPosition_.X) * 0.5f, (selectionEndPosition_.Y - selectionStartPosition_.Y) * 0.5f, 3000.f);
	FVector midPoint = FVector(selectionStartPosition_.X + extent.X, selectionStartPosition_.Y + extent.Y, selectionStartPosition_.Z - extent.Z * 0.5f);
	extent = FVector(abs(extent.X), abs(extent.Y), extent.Z);

	multipleSelectionBox_->SetWorldLocation(midPoint);
	multipleSelectionBox_->SetBoxExtent(extent);

	TArray<AActor*> overlappingActors;
	multipleSelectionBox_->GetOverlappingActors(overlappingActors);

	for (auto character : spectatorPawn->selectedCharacters_)
	{
		character->SetIsSelected(false);
	}
	spectatorPawn->selectedCharacters_.Empty();

	for (auto actor : overlappingActors)
	{
		ARTSBR_Character* const character = Cast<ARTSBR_Character>(actor);

		if (character)
		{
			character->SetIsSelected(true);
			spectatorPawn->selectedCharacters_.Add(character);
		}
	}
}

void ARTSBR_PlayerController::Command()
{
	ARTSBR_SpectatorPawn *spectatorPawn;
	if ((spectatorPawn = Cast<ARTSBR_SpectatorPawn>(GetPawn())) != nullptr)
	{
		FHitResult hit;
		if(GetHitResultUnderCursor(ECC_Visibility, false, hit))
		{
			for (auto actor : spectatorPawn->selectedCharacters_)
			{
				ARTSBR_Character* const character = Cast<ARTSBR_Character>(actor);

				if (character)
				{

					character->MoveToDestination(hit.Location);
				}
			}
		}
	}
}
