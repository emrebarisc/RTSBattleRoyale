// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSBR_HUD.h"

#include "Components/CapsuleComponent.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"

#include "RTSBR_Character.h"
#include "RTSBR_SpectatorPawn.h"

ARTSBR_HUD::ARTSBR_HUD()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARTSBR_HUD::BeginPlay()
{
	Super::BeginPlay();
}

void ARTSBR_HUD::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
}

void ARTSBR_HUD::DrawHUD()
{
	Super::DrawHUD();

	if (GEngine && GEngine->GameViewport)
	{
		FVector2D viewportSize;
		GEngine->GameViewport->GetViewportSize(viewportSize);
		uiScale_ = viewportSize.X / 2048.f;
	}
	
	ShowHealthBars();
}

ARTSBR_PlayerController * ARTSBR_HUD::GetPlayerController() const
{
	return nullptr;
}

ARTSBR_SpectatorPawn *ARTSBR_HUD::GetSpectatorPawn() const
{
	return nullptr;
}

void ARTSBR_HUD::ShowHealthBars() const
{
	for (FConstPawnIterator pawn = GetWorld()->GetPawnIterator(); pawn; ++pawn)
	{
		ARTSBR_Character* character = Cast<ARTSBR_Character>(*pawn);
		if (character && character->GetHealth() > 0)
		{
			FVector center = character->GetActorLocation();
			FVector extent = FVector(60.f, 34.f, 131.75f);

			FVector2D center2D = FVector2D(Canvas->Project(FVector(center.X, center.Y, center.Z + extent.Z)));

			float actorExtent = 50.f;
			float healthPercentage = 0.5f;
			float yOffset = 10.f;

			healthPercentage = character->GetHealth() / character->GetMaxHealth();
			actorExtent = character->GetCapsuleComponent()->GetScaledCapsuleRadius();

			FVector pos1 = Canvas->Project(FVector(center.X, center.Y - actorExtent * 2, center.Z + extent.Z));
			FVector pos2 = Canvas->Project(FVector(center.X, center.Y + actorExtent * 2, center.Z + extent.Z));

			float barWidth = (pos2 - pos1).Size2D();
			float barHeight = barWidth * 0.2f;

			ARTSBR_PlayerController* playerController = GetPlayerController();

			/* Background tile */
			barWidth += 2.f;
			barHeight += 2.f;

			float x = center2D.X - barWidth * 0.5f;
			float y = center2D.Y;

			FCanvasTileItem tileItem(FVector2D(x, y), FVector2D(barWidth, barHeight), FLinearColor(0.0f, 0.0f, 0.0f, 0.5f));
			tileItem.BlendMode = SE_BLEND_Translucent;
			Canvas->DrawItem(tileItem);
			/* Background tile */

			/* Health tile */
			barWidth -= 2.f;
			barHeight -= 2.f;

			x = center2D.X - barWidth * 0.5f;
			y = center2D.Y + 1.f;

			tileItem.Position = FVector2D(x, y);
			tileItem.SetColor(FLinearColor(1.0f, 1.0f, 0.3f, 1.f));
			tileItem.Size = FVector2D(barWidth * healthPercentage, barHeight);
			Canvas->DrawItem(tileItem);
		}
	}
}

void ARTSBR_HUD::ShowSelectionGrid(FVector2D gridStartPos)
{

}
