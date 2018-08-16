// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSBR_GameMode.h"
#include "RTSBR_GameState.h"
#include "RTSBR_PlayerController.h"
#include "RTSBR_SpectatorPawn.h"
#include "RTSBR_HUD.h"
#include "RTSBR_PlayerState.h"

ARTSBR_GameMode::ARTSBR_GameMode()
{
	GameStateClass = ARTSBR_GameState::StaticClass();
	PlayerControllerClass = ARTSBR_PlayerController::StaticClass();
	SpectatorClass = ARTSBR_SpectatorPawn::StaticClass();
	DefaultPawnClass = ARTSBR_SpectatorPawn::StaticClass();
	PlayerStateClass = ARTSBR_PlayerState::StaticClass();
	HUDClass = ARTSBR_HUD::StaticClass();
}
