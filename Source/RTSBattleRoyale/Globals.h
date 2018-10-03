// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class Team : uint8
{
	Spectator = 0,
	TeamOne,
	TeamTwo,
	TeamThree,
	TeamFour,
	TeamFive,
	TeamSix,
	TeamSeven,
	TeamEight,
	TeamNine,
	TeamTen
};

/**
 * 
 */
class RTSBATTLEROYALE_API Globals
{
public:
	Globals();
	~Globals();
};
