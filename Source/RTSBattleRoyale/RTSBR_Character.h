// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RTSBR_Character.generated.h"

class Damage
{
public:
	Damage() : physicalDamage(0.f), magicDamage(0.f)
	{}

	Damage(const float physicalDmg, const float magicDmg) : physicalDamage(physicalDmg), magicDamage(magicDmg)
	{}

	float physicalDamage;
	float magicDamage;
};

UCLASS()
class RTSBATTLEROYALE_API ARTSBR_Character : public ACharacter
{
	GENERATED_BODY()

public:
	ARTSBR_Character();

	void ApplyDamage(const Damage &damage);

	bool GetIsAttacking() const
	{
		return isAttacking_;
	}

protected:
	virtual void Attack();
	virtual float CalculateDamage();
	virtual void Die();

	Damage damage_;
	float health_;
	float armor_;
	float magicResistance_;
	float attackSpeed_;

	bool isAttacking_;

private:	
	virtual void Tick(float deltaTime) override;
	virtual void BeginPlay() override;

};