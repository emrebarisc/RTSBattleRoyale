// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "RTSBR_GameState.generated.h"

/**
 * 
 */
UCLASS()
class RTSBATTLEROYALE_API ARTSBR_GameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ARTSBR_GameState();

	void BeginPlay() override;
	void Tick(float deltaSeconds) override;

	/** World bounds for mini map & camera movement. */
	FBox worldBounds;
};
