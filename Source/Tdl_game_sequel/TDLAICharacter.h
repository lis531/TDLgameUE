// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "TDLPlayer.h"
#include "TDLAI_Controller.h"
#include "TDLAICharacter.generated.h"

class ATDLPlayer;
class ATDLAI_Character;
class APawn;

UCLASS()
class TDL_GAME_SEQUEL_API ATDLAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATDLAICharacter();

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AAIController> PlayerAIControllerClassBP;

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:	
	ATDLAI_Controller* AIBrain;
	ATDLPlayer* TargetPlayer;

};
