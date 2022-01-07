// Fill out your copyright notice in the Description page of Project Settings.

#include "TDLPodziemieGameMode.h"

ATDLPodziemieGameMode::ATDLPodziemieGameMode()
{
	// Ustawianie default Pawn klasy
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/BP_TDLPlayer"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}