// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSBR_Archer.h"

#include "ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"

#include "BaseStats.h"
#include "RTSBR_Character_AnimInstance.h"

ARTSBR_Archer::ARTSBR_Archer() : ARTSBR_Character()
{
	health_ = BaseStats::BaseArcherStats::HEALTH;
	armor_ = BaseStats::BaseArcherStats::ARMOR;
	magicResistance_ = BaseStats::BaseArcherStats::MAGIC_RESISTANCE;
	attackSpeed_ = BaseStats::BaseArcherStats::PHYSICAL_DAMAGE;
	damage_.physicalDamage = BaseStats::BaseArcherStats::MAGIC_DAMAGE;
	damage_.magicDamage = BaseStats::BaseArcherStats::ATTACK_SPEED;
}