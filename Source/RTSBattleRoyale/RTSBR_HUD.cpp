// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSBR_HUD.h"

#include "Components/CapsuleComponent.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"

#include "RTSBR_Character.h"
#include "RTSBR_SpectatorPawn.h"
#include "RTSBR_PlayerController.h"
#include "ConstructorHelpers.h"

ARTSBR_HUD::ARTSBR_HUD()
{
	PrimaryActorTick.bCanEverTick = false;

	const ConstructorHelpers::FObjectFinder<UTexture2D> topInfoBarTextureAsset(TEXT("Texture2D'/Game/Assets/Textures/TopUIBar.TopUIBar'"));
	if (topInfoBarTextureAsset.Object) topInfoBarTexture_ = topInfoBarTextureAsset.Object;

	const ConstructorHelpers::FObjectFinder<UFont> uiFontAsset(TEXT("Font'/Game/Assets/Fonts/SpindleRefined-Regular_Font.SpindleRefined-Regular_Font'"));
	if (uiFontAsset.Object) uiFont_ = uiFontAsset.Object;
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
	
	DrawHealthBars();

	if(GetPlayerController()->GetIsSelectionActive())
	{
		const FVector selectionStartPosition = Canvas->Project(GetPlayerController()->GetSelectionStartPosition());

		DrawSelectionGrid(FVector2D(selectionStartPosition));
	}

	DrawTopInfoBar();
}

ARTSBR_PlayerController * ARTSBR_HUD::GetPlayerController() const
{
	return Cast<ARTSBR_PlayerController>(PlayerOwner);
}

ARTSBR_SpectatorPawn *ARTSBR_HUD::GetSpectatorPawn() const
{
	ARTSBR_PlayerController *pc = GetPlayerController();
	if (pc)
	{
		return pc->GetMainSpectatorPawn();
	}

	return nullptr;
}

void ARTSBR_HUD::DrawHealthBars() const
{
	for (FConstPawnIterator pawn = GetWorld()->GetPawnIterator(); pawn; ++pawn)
	{
		ARTSBR_Character* character = Cast<ARTSBR_Character>(*pawn);
		if (character && character->GetHealth() > 0)
		{
			const FVector center = character->GetActorLocation();
			const FVector extent = FVector(60.f, 34.f, 131.75f);

			const FVector2D center2D = FVector2D(Canvas->Project(FVector(center.X, center.Y, center.Z + extent.Z)));

			float actorExtent = 50.f;
			float healthPercentage = 0.5f;
			float yOffset = 10.f;

			healthPercentage = character->GetHealth() / character->GetMaxHealth();
			actorExtent = character->GetCapsuleComponent()->GetScaledCapsuleRadius();

			const FVector pos1 = Canvas->Project(FVector(center.X, center.Y - actorExtent * 2, center.Z + extent.Z));
			const FVector pos2 = Canvas->Project(FVector(center.X, center.Y + actorExtent * 2, center.Z + extent.Z));

			float barWidth = (pos2 - pos1).Size2D();
			float barHeight = barWidth * 0.2f;

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

void ARTSBR_HUD::DrawSelectionGrid(FVector2D gridStartPos) const
{
	FVector2D mousePosition;
	GetPlayerController()->GetMousePosition(mousePosition.X, mousePosition.Y);

	float gridWidth = mousePosition.X - gridStartPos.X;
	float gridHeight = mousePosition.Y - gridStartPos.Y;

	FCanvasTileItem fillTileItem(gridStartPos, FVector2D(gridWidth, gridHeight), FLinearColor(1.0f, 1.0f, 1.0f, 0.2f));
	fillTileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(fillTileItem);

	FCanvasTileItem tileItem(gridStartPos, FVector2D(gridWidth, 1.f), FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	tileItem.BlendMode = SE_BLEND_Translucent;
	tileItem.UV1 = FVector2D(gridWidth * 0.1f, 1.f);
	Canvas->DrawItem(tileItem);

	tileItem.Position = gridStartPos + FVector2D(0.f, gridHeight);
	Canvas->DrawItem(tileItem);

	tileItem.Position = gridStartPos;
	tileItem.Size = FVector2D(1.f, gridHeight);
	tileItem.UV1 = FVector2D(1.f, gridHeight * 0.1f);
	Canvas->DrawItem(tileItem);

	tileItem.Position = gridStartPos + FVector2D(gridWidth, 0.f);
	Canvas->DrawItem(tileItem);
}

void ARTSBR_HUD::DrawTopInfoBar()
{
	const float gridWidth = GEngine->GameViewport->Viewport->GetSizeXY().X;
	const float gridHeight = 30.f;

	FCanvasTileItem tileItem(FVector2D::ZeroVector, topInfoBarTexture_->Resource, FVector2D(gridWidth, gridHeight), FLinearColor(1.f, 1.f, 1.f, 1.f));
	tileItem.BlendMode = SE_BLEND_Translucent;
	tileItem.UV1 = FVector2D(0.5f, 0.5f);
	Canvas->DrawItem(tileItem);

	const FString gameText("REAL TIME STRATEGY BATTLE ROYALE");
	float textWidth = 0;
	float textHeight = 0;
	GetTextSize(gameText, textWidth, textHeight, uiFont_);
	DrawText(gameText, FLinearColor::White, (gridWidth - textWidth) * 0.5f, (gridHeight - textHeight) * 0.5f, uiFont_);
}