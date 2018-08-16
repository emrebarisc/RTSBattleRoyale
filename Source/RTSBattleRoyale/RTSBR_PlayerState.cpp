// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSBR_PlayerState.h"


ARTSBR_PlayerState::ARTSBR_PlayerState()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARTSBR_PlayerState::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void ARTSBR_PlayerState::BeginPlay()
{
	Super::BeginPlay();
}