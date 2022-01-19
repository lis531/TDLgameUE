// Fill out your copyright notice in the Description page of Project Settings.

#include "TDLAICharacter.h"

ATDLAICharacter::ATDLAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATDLAICharacter::BeginPlay()
{
	Super::BeginPlay();

	TargetPlayer = Cast<ATDLPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// Initialize the AIBrain
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.OverrideLevel = GetLevel();
	SpawnInfo.ObjectFlags |= RF_Transient;
	AIBrain = GetWorld()->SpawnActor<ATDLAI_Controller>(GetActorLocation(), GetActorRotation(), SpawnInfo);

	if (AIBrain)
		AIBrain->Possess(this);
	else
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("FAILED TO INITIALIZE AIBRAIN!"));
	
}

void ATDLAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AIBrain->MoveToActor(TargetPlayer);
}