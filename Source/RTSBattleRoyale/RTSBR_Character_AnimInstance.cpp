// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSBR_Character_AnimInstance.h"

#include "RTSBR_Character.h"

void URTSBR_Character_AnimInstance::UpdateAnimationProperties()
{
	const APawn *character = TryGetPawnOwner();
	const ARTSBR_Character *rtsbrCharacter;

	if(character && (rtsbrCharacter = Cast<ARTSBR_Character>(character)) != nullptr)
	{
		isCharacterAttacking_ = rtsbrCharacter->GetIsAttacking();
		characterMovementSpeed_ = rtsbrCharacter->GetVelocity().Size();
	}
}