// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineUtils.h"

#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

#include "GameFramework/Actor.h"
#include "Drzwi.generated.h"

class UStaticMeshComponent;
class UAudioComponent;

UCLASS()
class TDL_GAME_SEQUEL_API ADrzwi : public AActor
{
	GENERATED_BODY()
	
public:	
	ADrzwi();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"));
		UStaticMeshComponent* DoorFrameMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"));
		UStaticMeshComponent* DoorLeftMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"));
		UStaticMeshComponent* DoorRightMesh;

	bool areOpen = false;

	void Open();
	void Close();

protected:
	virtual void BeginPlay() override;

private:	
	UAudioComponent* audioComponent;
	USoundCue* DoorSoundCue;
	FTimerHandle closeTimerHandle;
};