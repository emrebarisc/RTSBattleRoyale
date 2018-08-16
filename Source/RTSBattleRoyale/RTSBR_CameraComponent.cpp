// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSBR_CameraComponent.h"

#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpectatorPawn.h"


#include "RTSBR_PlayerController.h"
#include "RTSBR_SpectatorPawn.h"
#include "RTSBR_SpectatorPawnMovement.h"
#include "Engine/Engine.h"

URTSBR_CameraComponent::URTSBR_CameraComponent()
{
	bShouldClampCamera_ = true;

	zoomAlpha_ = 1.f;
	cameraScrollSpeed_ = 3000.f;
	cameraActiveBorder_ = 100.f;
	minZoomLevel_ = 0.4f;
	maxZoomLevel_ = 1.f;
	minCameraOffset_ = 0.f;
	maxCameraOffset_ = 20000.f;
	movementSpeed_ = 100.f;

	fixedCameraAngle_ = FRotator(-60.f, 0.f, 0.f);
}

void URTSBR_CameraComponent::GetCameraView(float deltaTime, FMinimalViewInfo& desiredView)
{
	APlayerController* playerController = GetPlayerController();

	if (playerController)
	{
		desiredView.FOV = 30.f;
		const float currentOffset = minCameraOffset_ + zoomAlpha_ * (maxCameraOffset_ - minCameraOffset_);
		const FVector focalPos = playerController->GetFocalLocation();
		desiredView.Location = focalPos - fixedCameraAngle_.Vector() * currentOffset;
		desiredView.Rotation = fixedCameraAngle_;
	}
}

void URTSBR_CameraComponent::OnZoomIn()
{
	SetZoomLevel(zoomAlpha_ - 0.1f);
}

void URTSBR_CameraComponent::OnZoomOut()
{
	SetZoomLevel(zoomAlpha_ + 0.1f);
}

void URTSBR_CameraComponent::UpdateCameraMovement(const APlayerController* playerController) const
{
	ULocalPlayer* const localPlayer = Cast<ULocalPlayer>(playerController->Player);

	if(localPlayer && localPlayer->ViewportClient && localPlayer->ViewportClient->Viewport)
	{
		FVector2D mousePosition;
		if(!localPlayer->ViewportClient->GetMousePosition(mousePosition))
		{
			return;
		}

		FViewport* viewport = localPlayer->ViewportClient->Viewport;
		const float scrollSpeed = 60.f;
		const FIntPoint viewportSize = viewport->GetSizeXY();

		const uint32 viewLeft = FMath::TruncToInt(localPlayer->Origin.X * viewportSize.X);
		const uint32 viewRight = viewLeft + FMath::TruncToInt(localPlayer->Size.X * viewportSize.X);
		const uint32 viewTop = FMath::TruncToInt(localPlayer->Origin.Y * viewportSize.Y);
		const uint32 viewBottom = viewTop + FMath::TruncToInt(localPlayer->Size.Y * viewportSize.Y);

		const float maxSpeed = cameraScrollSpeed_ * FMath::Clamp(zoomAlpha_, minZoomLevel_, maxZoomLevel_);

		const uint32 mouseX = mousePosition.X;
		const uint32 mouseY = mousePosition.Y;
		float spectatorCameraSpeed = maxSpeed;
		ARTSBR_SpectatorPawn *spectatorPawn = nullptr;
		
		if(true) //!bNoScrollZone_
		{
			if (mouseX >= viewLeft && mouseX <= (viewLeft + cameraActiveBorder_))
			{
				const float delta = 1.0f - float(mouseX - viewLeft) / cameraActiveBorder_;
				spectatorCameraSpeed = delta * maxSpeed;
				MoveRight(-scrollSpeed * delta);
			}
			else if (mouseX >= (viewRight - cameraActiveBorder_) && mouseX <= viewRight)
			{
				const float delta = float(mouseX - viewRight + cameraActiveBorder_) / cameraActiveBorder_;
				spectatorCameraSpeed = delta * maxSpeed;
				MoveRight(scrollSpeed * delta);
			}

			if (mouseY >= viewTop && mouseY <= (viewTop + cameraActiveBorder_))
			{
				const float delta = 1.0f - float(mouseY - viewTop) / cameraActiveBorder_;
				spectatorCameraSpeed = delta * maxSpeed;
				MoveForward(scrollSpeed * delta);
			}
			else if (mouseY >= (viewBottom - cameraActiveBorder_) && mouseY <= viewBottom)
			{
				const float delta = float(mouseY - (viewBottom - cameraActiveBorder_)) / cameraActiveBorder_;
				spectatorCameraSpeed = delta * maxSpeed;
				MoveForward(-scrollSpeed * delta);
			}
		}
	}
}

void URTSBR_CameraComponent::MoveForward(const float value) const
{
	APawn* ownerPawn = GetOwnerPawn();

	if (ownerPawn)
	{
		APlayerController* controller = GetPlayerController();
		if (value != 0.f && controller)
		{
			// If our camera is not rotated or we want to use camera's local coordinates, we can use rotationMatrix
			//const FRotationMatrix rotationMatrix(controller->PlayerCameraManager->GetCameraRotation());
			const FVector worldSpaceAcc = /*rotationMatrix.GetScaledAxis(EAxis::X)*/ FVector(1.f, 0.f, 0.f) * movementSpeed_;
			
			ownerPawn->AddMovementInput(worldSpaceAcc, value);
		}
	}
}

void URTSBR_CameraComponent::MoveRight(const float value) const
{
	APawn* ownerPawn = GetOwnerPawn();

	if (ownerPawn)
	{
		APlayerController* controller = GetPlayerController();
		if (value != 0.f && controller)
		{
			// If our camera is not rotated or we want to use camera's local coordinates, we can use rotationMatrix
			//const FRotationMatrix rotationMatrix(controller->PlayerCameraManager->GetCameraRotation());
			const FVector worldSpaceAcc = /*rotationMatrix.GetScaledAxis(EAxis::Y)*/ FVector(0.f, 1.f, 0.f) * movementSpeed_;

			ownerPawn->AddMovementInput(worldSpaceAcc, value);
		}
	}
}

void URTSBR_CameraComponent::SetZoomLevel(float level)
{
	zoomAlpha_ = FMath::Clamp(level, minZoomLevel_, maxZoomLevel_);
}

void URTSBR_CameraComponent::ClampCameraLocation(const APlayerController *playerController, FVector& outCameraLocation) const
{
	if (bShouldClampCamera_)
	{
		UpdateCameraBounds(playerController);
		if (cameraMovementBounds_.GetSize() != FVector::ZeroVector)
		{
			outCameraLocation = cameraMovementBounds_.GetClosestPointTo(outCameraLocation);
		}
	}
}

APawn* URTSBR_CameraComponent::GetOwnerPawn() const
{
	return Cast<APawn>(GetOwner());
}

ARTSBR_PlayerController* URTSBR_CameraComponent::GetPlayerController() const
{
	ARTSBR_PlayerController* controller = nullptr;
	APawn* owner = GetOwnerPawn();
	if (owner)
	{
		controller = Cast<ARTSBR_PlayerController>(owner->GetController());
	}

	return controller;
}

void URTSBR_CameraComponent::UpdateCameraBounds(const APlayerController* playerController) const
{
	ULocalPlayer* const localPlayer = Cast<ULocalPlayer>(playerController->Player);
	if (localPlayer == NULL || localPlayer->ViewportClient == NULL)
	{
		return;
	}

	FVector2D currentViewportSize;
	localPlayer->ViewportClient->GetViewportSize(currentViewportSize);

	if (cameraMovementBounds_.GetSize() == FVector::ZeroVector || currentViewportSize != cameraMovementViewportSize_)
	{
		const FVector frustumRay2DDir = FVector(1, 1, 0).GetSafeNormal();
		const FVector frustumRay2DRight = FVector::CrossProduct(frustumRay2DDir, FVector::UpVector);
		const FQuat rotationQuat(frustumRay2DRight, FMath::DegreesToRadians(90.f - playerController->PlayerCameraManager->GetFOVAngle() * 0.5f));
		const FVector frustumRayDir = rotationQuat.RotateVector(frustumRay2DDir);
	}
}
