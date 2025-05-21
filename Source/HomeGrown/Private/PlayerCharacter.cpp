// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Carrot.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(RootComponent);

	// Initialize with default values
	PlantClass = nullptr;
}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();



	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			UEnhancedInputLocalPlayerSubsystem* Subsystem =
				LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
			if (Subsystem && DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		}
		if (LookAction)
		{
			EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		}
		if (InteractAction)
		{
			EnhancedInput->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::LineTrace);
		}
	}

}

void APlayerCharacter::SpawnPlant(FVector spawnLocation)
{
	UE_LOG(LogTemp, Warning, TEXT("Spawned at: %s"), *spawnLocation.ToString());
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), Input.Y);
	AddMovementInput(GetActorRightVector(), Input.X);
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();
	AddControllerYawInput(-Input.X);
	AddControllerPitchInput(Input.Y);
}

void APlayerCharacter::LineTrace()
{
    if (!Camera)
    {
        UE_LOG(LogTemp, Error, TEXT("Camera is null!"));
        return;
    }

    FHitResult HitResult;
    FVector Start = Camera->GetComponentLocation();
    FVector End = Start + (Camera->GetForwardVector() * 1000.0f);

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult, Start, End, ECC_WorldStatic, Params
    );

    // Debug Drawing
    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f);
    if (bHit) DrawDebugPoint(GetWorld(), HitResult.ImpactPoint, 15.0f, FColor::Green, false, 2.0f);

    if (bHit)
    {
        UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitResult.GetActor()->GetName());

        if (!PlantClass)
        {
            UE_LOG(LogTemp, Error, TEXT("PlantClass is NOT assigned!"));
            return;
        }

        FVector SpawnLocation = HitResult.ImpactPoint + (HitResult.ImpactNormal * 5.0f);

        FActorSpawnParameters SpawnParams;
        // Changed to AlwaysSpawn - will spawn regardless of collisions
        SpawnParams.SpawnCollisionHandlingOverride =
            ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
            PlantClass,
            FTransform(SpawnLocation),
            SpawnParams
        );

        if (SpawnedActor)
        {
            UE_LOG(LogTemp, Warning, TEXT("SPAWNED: %s"), *SpawnedActor->GetName());
            DrawDebugSphere(GetWorld(), SpawnLocation, 25.0f, 12, FColor::Blue, false, 3.0f);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("FAILED TO SPAWN!"));
        }
    }
}


