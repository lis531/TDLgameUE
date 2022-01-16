#pragma once

#include "CoreMinimal.h"
#include "AI_Controller.h"
#include "AI_Controller.generated.h"

UCLASS()
class TDL_GAME_SEQUEL_API AAI_Controller : public AAIController
{
	GENERATED_BODY()
	
public:
	AAI_Controller();

	virtual void BeginPlay() override;

	virtual void Possess(APawn* Pawn) override;

	virtual void Tick(float DeltaTime) override;

	virtual FRotator GetControlRotation() const override;

	UFUNCTION()
	void OnPawnDetected(const TArray<UObject*>& DetectedPawns);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	float AISightRadius = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	float AISightAge = 5.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	float AILoseSightRadius = AISightRadius + 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	float AIFieldOfView = 90.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	class UAISenseConfig_Sight* SightConfig;
};