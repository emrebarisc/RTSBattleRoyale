// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "RTSBR_SpectatorPawn.generated.h"

class URTSBR_CameraComponent;

/**
 * 
 */
UCLASS()
class RTSBATTLEROYALE_API ARTSBR_SpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()
	
public:
	ARTSBR_SpectatorPawn(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	
	URTSBR_CameraComponent* GetCameraComponent()
	{
		return cameraComponent_;
	}

private:
	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);
	void OnMouseScrollUp();
	void OnMouseScrollDown();

	URTSBR_CameraComponent* cameraComponent_;
};
