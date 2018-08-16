// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTSBR_HUD.generated.h"

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
};
