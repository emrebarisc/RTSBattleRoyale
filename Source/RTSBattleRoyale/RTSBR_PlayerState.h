// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RTSBR_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class RTSBATTLEROYALE_API ARTSBR_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ARTSBR_PlayerState();

	void Tick(float deltaTime) override;
	void BeginPlay() override;
};
