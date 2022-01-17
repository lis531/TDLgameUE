// Fill out your copyright notice in the Description page of Project Settings.


#include "TDLAICharacter.h"

// Sets default values
ATDLAICharacter::ATDLAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIBrain = CreateAI
	AIBrain.SetPawn(this);
}

// Called when the game starts or when spawned
void ATDLAICharacter::BeginPlay()
{
	Super::BeginPlay();

	TargetPlayer = Cast<ATDLPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

// Called every frame
void ATDLAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AIBrain.MoveToActor(TargetPlayer);
}

// Called to bind functionality to input
void ATDLAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

