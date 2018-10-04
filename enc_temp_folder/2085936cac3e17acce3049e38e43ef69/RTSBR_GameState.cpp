// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSBR_GameState.h"


ARTSBR_GameState::ARTSBR_GameState() : isGameActive_(true)
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARTSBR_GameState::BeginPlay()
{
	Super::BeginPlay();
}

void ARTSBR_GameState::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
}
