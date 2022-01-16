// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Controller.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AAI_Controller::AAI_Controller()
{
    PrimaryActorTick.bCanEverTick = true;

    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
    SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

    SightConfig->SightRadius = AISightRadius;
    SightConfig->LoseSightRadius = AILoseSightRadius;
    SightConfig->PreipheralVisionAngleDegrees = AIFieldOfView;
    SightConfig->SetMaxAge(AISightAge);

    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

    GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
    GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AAI_Controller::OnPawnDetected);
    GetPerceptionComponent()->ConfigureSense(*SightConfig);
}

void AAI_Controller::BeginPlay()
{
    Super::BeginPlay();

    if(GetPerceptionComponent() != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Gut gut"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Gut gut nicht gut"));
    }

}    
void AAI_Controller::Possess(APawn* Pawn)
{
    Super::Possess(Pawn);
}
void AAI_Controller::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
void AAI_Controller::GetControlRotation() const
{
    if(GetPawn() == nullptr)
    {
        return FRotator(0.0f, 0.0f, 0.0f);
    }
    return FRotator(0.0f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}
void AAI_Controller::OnPawnDetected(TArray<AActor*> DetectedPawns)
{

}