// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawnMovement.h"
#include "RTSBR_SpectatorPawnMovement.generated.h"

/**
 * 
 */
UCLASS()
class RTSBATTLEROYALE_API URTSBR_SpectatorPawnMovement : public USpectatorPawnMovement
{
	GENERATED_BODY()
	
public:
	URTSBR_SpectatorPawnMovement();

private:
	virtual void TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) override;

	bool bInitialLocationSet_;
};
