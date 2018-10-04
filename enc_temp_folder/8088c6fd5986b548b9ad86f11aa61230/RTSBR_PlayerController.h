// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSBR_PlayerController.generated.h"

class ARTSBR_SpectatorPawn;
class UBoxComponent;

/**
 * 
 */
UCLASS()
class RTSBATTLEROYALE_API ARTSBR_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARTSBR_PlayerController();

	ARTSBR_SpectatorPawn *GetMainSpectatorPawn() const;

protected:
	virtual void SetupInputComponent() override;
	virtual void ProcessPlayerInput(const float deltaTime, const bool bGamePaused) override;

private:
	void MovePawnForward(float value);
	void MovePawnRight(float value);
	void ZoomIn();
	void ZoomOut();

	void StartSelection();
	void EndSelection();
	void UnitSelection() const;

	void Command();

	FVector selectionStartPosition_;
	FVector selectionEndPosition_;
	UBoxComponent* multipleSelectionBox_;
};
