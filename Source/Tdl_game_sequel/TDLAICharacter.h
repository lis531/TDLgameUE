// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "TDLPlayer.h"
#include "TDLAICharacter.generated.h"

class ATDLPlayer;
class APawn;

UCLASS()
class TDL_GAME_SEQUEL_API ATDLAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATDLAICharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:	
	AAIController* AIBrain;
	ATDLPlayer* TargetPlayer;

};
