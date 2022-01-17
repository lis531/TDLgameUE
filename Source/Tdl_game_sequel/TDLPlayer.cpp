// Fill out your copyright notice in the Description page of Project Settings.


#include "TDLPlayer.h"

ATDLPlayer::ATDLPlayer()
{
	GetCapsuleComponent()->InitCapsuleSize(20.0f, 65.0f);

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 61.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	static ConstructorHelpers::FObjectFinder<USoundCue> stepSoundCueObject(TEXT("SoundCue'/Game/Player/Stepping'"));
	if (stepSoundCueObject.Succeeded())
	{
		SteppingSoundCue = stepSoundCueObject.Object;

		StepAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SteppingAudioComponent"));
		StepAudioComponent->SetupAttachment(RootComponent);
		StepAudioComponent->SetSound(SteppingSoundCue);
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, "Failed to load the SteppingSoundCue!");

	Flashlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight"));
	Flashlight->SetupAttachment(FirstPersonCameraComponent);
	Flashlight->Intensity = 10000.0f;
	Flashlight->AttenuationRadius = 2000.0f;


	previousStepPos = GetActorLocation();
}

void ATDLPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = this->WalkingSpeed;
}

void ATDLPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentPos = GetActorLocation();
	if (FVector::Dist(previousStepPos, CurrentPos) > OffsetBetweenSteps)
	{
		StepAudioComponent->Play();
		previousStepPos = CurrentPos;
	}
}

void ATDLPlayer::MoveVertically(float value)
{
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(dir, value);
}
void ATDLPlayer::MoveHorizontally(float value)
{
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(dir, value);
}

void ATDLPlayer::LookVertically(float value)
{
	AddControllerPitchInput(value * this->LookSensitivity);
}
void ATDLPlayer::LookHorizontally(float value)
{
	AddControllerYawInput(value * this->LookSensitivity);
}

void ATDLPlayer::StartJump()
{
	bPressedJump = true;
}
void ATDLPlayer::StopJump()
{
	bPressedJump = false;
}

void ATDLPlayer::StartCrouch()
{
	Crouch();
}
void ATDLPlayer::StopCrouch()
{
	UnCrouch();
}

void ATDLPlayer::StartSprint()
{
	this->bPressedSprint = true;
	GetCharacterMovement()->MaxWalkSpeed = this->RunningSpeed;
}
void ATDLPlayer::StopSprint()
{
	this->bPressedSprint = false;
	GetCharacterMovement()->MaxWalkSpeed = this->WalkingSpeed;
}

void ATDLPlayer::Interact()
{
	FHitResult hit;
	FVector cameraPos;
	FRotator cameraDir;

	GetController()->GetPlayerViewPoint(cameraPos, cameraDir);

	FVector rayStart = cameraPos;
	FVector rayEnd = rayStart + (cameraDir.Vector() * InteractionDistance);

	FCollisionQueryParams traceParams;
	bool hitSomething = GetWorld()->LineTraceSingleByChannel(hit, rayStart, rayEnd, ECC_Visibility, traceParams);

#ifdef DRAW_DEBUG
	DrawDebugLine(GetWorld(), rayStart, rayEnd, FColor::Cyan, false, 2.0f);
#endif 

	if (hitSomething)
	{
#ifdef DRAW_DEBUG
		DrawDebugBox(GetWorld(), hit.ImpactPoint, FVector(4, 4, 4), FColor::Emerald, false, 2.0f);
		AActor* hitActor = hit.GetActor();

		// Jezeli trafiono aktora "Drzwi"
		if (hitActor->ActorHasTag(TEXT("Door")))
		{
			UStaticMeshComponent* hitMesh = Cast<UStaticMeshComponent>(hit.GetComponent());
			
			// Jezeli trafiono drzwi (te przesuwane)
			if (hitMesh->ComponentHasTag(TEXT("DoorInteractable")))
				Cast<ADrzwi>(hitActor)->Open();
			
		}

#endif 
	}
}

void ATDLPlayer::ToggleFlashlight()
{
	Flashlight->ToggleVisibility();
}

// Called to bind functionality to input
void ATDLPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Poruszanie sie
	PlayerInputComponent->BindAxis("Horizontal", this, &ATDLPlayer::MoveHorizontally);
	PlayerInputComponent->BindAxis("Vertical", this, &ATDLPlayer::MoveVertically);

	// Rozgladanie sie
	PlayerInputComponent->BindAxis("MouseY", this, &ATDLPlayer::LookVertically);
	PlayerInputComponent->BindAxis("MouseX", this, &ATDLPlayer::LookHorizontally);

	// Skakanie
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATDLPlayer::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ATDLPlayer::StopJump);

	// Kucanie
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ATDLPlayer::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ATDLPlayer::StopCrouch);

	// Bieganie
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ATDLPlayer::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ATDLPlayer::StopSprint);

	// Interakcje
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ATDLPlayer::Interact);
	PlayerInputComponent->BindAction("Flashlight", IE_Pressed, this, &ATDLPlayer::ToggleFlashlight);
}