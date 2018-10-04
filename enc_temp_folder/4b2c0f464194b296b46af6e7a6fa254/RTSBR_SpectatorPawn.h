// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "RTSBR_SpectatorPawn.generated.h"

class ARTSBR_Character;
class URTSBR_CameraComponent;

/**
 * 
 */
UCLASS()
class RTSBATTLEROYALE_API ARTSBR_SpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

	friend class ARTSBR_PlayerController;

public:
	ARTSBR_SpectatorPawn(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	
	URTSBR_CameraComponent* GetCameraComponent() const
	{
		return cameraComponent_;
	}

	TArray<ARTSBR_Character*> const* GetSelectedCharacters() const
	{
		return &selectedCharacters_;
	}

private:
	void MoveForward(float value);
	void MoveRight(float value);
	void OnMouseScrollUp();
	void OnMouseScrollDown();

	TArray<ARTSBR_Character*> selectedCharacters_;

	URTSBR_CameraComponent* cameraComponent_;
};
