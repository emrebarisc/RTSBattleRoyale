// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RTSBR_Character_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RTSBATTLEROYALE_API URTSBR_Character_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float characterMovementSpeed_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool isCharacterAttacking_;

	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
	void UpdateAnimationProperties();
};
