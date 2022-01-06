// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tdl_game_sequelGameMode.h"
#include "Tdl_game_sequelHUD.h"
#include "Tdl_game_sequelCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATdl_game_sequelGameMode::ATdl_game_sequelGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATdl_game_sequelHUD::StaticClass();
}
