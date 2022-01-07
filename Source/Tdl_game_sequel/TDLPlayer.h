// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "Containers/Array.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "TDLPlayer.generated.h"

class UInputComponent;
class USceneComponent;
class UCameraComponent;
class UCharacterMovementController;

#define DRAW_DEBUG

UCLASS()
class TDL_GAME_SEQUEL_API ATDLPlayer : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	ATDLPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "3000.0", DefaultValue = 1000.0))
		float WalkingSpeed;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "3000.0", DefaultValue = 1600.0))
		float RunningSpeed;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.01", ClampMax = "2.0", DefaultValue = 1.0))
		float LookSensitivity = 1.0f;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "3000.0", DefaultValue = 50.0))
		float InteractionDistance;

	UFUNCTION()
		void MoveVertically(float value);

	UFUNCTION()
		void MoveHorizontally(float value);

	UFUNCTION()
		void LookVertically(float value);
	UFUNCTION()
		void LookHorizontally(float value);

	UFUNCTION()
		void StartJump();
	UFUNCTION()
		void StopJump();

	UFUNCTION()
		void StartCrouch();
	UFUNCTION()
		void StopCrouch();

	UFUNCTION()
		void StartSprint();
	UFUNCTION()
		void StopSprint();

	UFUNCTION()
		void Interact();

	bool bPressedSprint = false;
};