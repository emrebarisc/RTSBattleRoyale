// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTSBR_HUD.generated.h"

class ARTSBR_PlayerController;
class ARTSBR_SpectatorPawn;

/**
 * 
 */
UCLASS()
class RTSBATTLEROYALE_API ARTSBR_HUD : public AHUD
{
	GENERATED_BODY()
public:
	ARTSBR_HUD();

	void BeginPlay() override;
	void Tick(float deltaSeconds) override;

private:
	virtual void DrawHUD() override;
	ARTSBR_PlayerController* GetPlayerController() const;
	ARTSBR_SpectatorPawn* GetSpectatorPawn() const;

	void DrawHealthBars() const;
	void DrawSelectionGrid(FVector2D gridStartPos) const;
	void DrawTopInfoBar();

	FVector2D selectionGridStartPosition_;

	UTexture2D *topInfoBarTexture_;
	UFont *uiFont_;

	float uiScale_;
};
