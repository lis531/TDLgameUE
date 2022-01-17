// Fill out your copyright notice in the Description page of Project Settings.


#include "TDLAI_Controller.h"
#include "AI_Character.h"
#include "Waypoint.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ATDLAI_Controller::ATDLAI_Controller()
{
    PrimaryActorTick.bCanEverTick = true;

    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
    SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

    SightConfig->SightRadius = AISightRadius;
    SightConfig->LoseSightRadius = AILoseSightRadius;
    SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
    SightConfig->SetMaxAge(AISightAge);

    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

    GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
    GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &ATDLAI_Controller::OnPawnDetected);
    GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

void ATDLAI_Controller::BeginPlay()
{
    Super::BeginPlay();

    if (GetPerceptionComponent() != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Gut gut"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Gut gut nicht gut"));
    }

}    

void ATDLAI_Controller::OnPossess(APawn* Pawn1)
{
    Super::OnPossess(Pawn1);
}

void ATDLAI_Controller::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    AAI_Character* Character1 = Cast<AAI_Character>(GetPawn());
    if (Character1->NextWaypoint != nullptr)
    {
        MoveToActor(Character1->NextWaypoint, 5.0f);
    }
}


FRotator ATDLAI_Controller::GetControlRotation() const
{
    if (GetPawn() == nullptr)
    {
        return FRotator(0.0f, 0.0f, 0.0f);
    }

    return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);

}

void ATDLAI_Controller::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{

}