// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TDLAI.generated.h"

UCLASS()
class TDL_GAME_SEQUEL_API ATDLAI : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATDLAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
