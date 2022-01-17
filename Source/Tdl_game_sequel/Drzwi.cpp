// Fill out your copyright notice in the Description page of Project Settings.


#include "Drzwi.h"

// Sets default values
ADrzwi::ADrzwi()
{
	Tags.Add(FName(TEXT("Door")));

	PrimaryActorTick.bCanEverTick = true;

	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> doorFrameMeshObjectFinder(TEXT("StaticMesh'/Game/Podziemie/Meshe/DoorFrameMesh'"));
	DoorFrameMesh->SetStaticMesh(doorFrameMeshObjectFinder.Object);
	DoorFrameMesh->SetupAttachment(RootComponent);
	DoorFrameMesh->SetMobility(EComponentMobility::Static);

	SetRootComponent(DoorFrameMesh);

	DoorLeftMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorLeft"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> doorLeftMeshObjectFinder(TEXT("StaticMesh'/Game/Podziemie/Meshe/DoorLeftMesh'"));
	DoorLeftMesh->SetStaticMesh(doorLeftMeshObjectFinder.Object);
	DoorLeftMesh->SetupAttachment(DoorFrameMesh);
	DoorLeftMesh->ComponentTags.Add(FName(TEXT("DoorInteractable")));

	DoorRightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorRight"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> doorRightMeshObjectFinder(TEXT("StaticMesh'/Game/Podziemie/Meshe/DoorRightMesh'"));
	DoorRightMesh->SetStaticMesh(doorRightMeshObjectFinder.Object);
	DoorRightMesh->SetupAttachment(DoorFrameMesh);
	DoorRightMesh->ComponentTags.Add(FName(TEXT("DoorInteractable")));


	static ConstructorHelpers::FObjectFinder<USoundCue> doorSoundCueFinder(TEXT("SoundCue'/Game/Podziemie/Drzwi/DoorSoundCue'"));
	DoorSoundCue = doorSoundCueFinder.Object;

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("DoorAudioComp"));
	audioComponent->SetupAttachment(DoorFrameMesh);
	audioComponent->SetSound(DoorSoundCue);
	audioComponent->SetAutoActivate(false);
}
void ADrzwi::BeginPlay()
{
	Super::BeginPlay();
}
void ADrzwi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADrzwi::Open()
{
	if (!areOpen)
	{
		GetWorldTimerManager().SetTimer(closeTimerHandle, this, &ADrzwi::Close, 1.0f, false, 2.0f);

		audioComponent->Play();

		DoorLeftMesh->AddLocalOffset(FVector(-50, 0, 0));
		DoorRightMesh->AddLocalOffset(FVector(50, 0, 0));

		areOpen = true;
	}
}
void ADrzwi::Close()
{
	if (areOpen)
	{
		GetWorldTimerManager().ClearTimer(closeTimerHandle);

		audioComponent->Play();

		DoorLeftMesh->AddLocalOffset(FVector(50, 0, 0));
		DoorRightMesh->AddLocalOffset(FVector(-50, 0, 0));

		areOpen = false;
	}
}