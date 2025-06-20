// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Shop.h"
#include "Components/Button.h"
#include "GameFramework/InputSettings.h"
#include "Camera/CameraComponent.h"
#include "PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Carrot.h"
#include "Planting_Ground.h"
#include "MainMenuHUD.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(RootComponent);

	// Initialize with default values
	MainMenuHUD = nullptr;
	MainMenuHUDClass = nullptr;
	PlantClass = nullptr;
	PlayerHUDClass = nullptr;
	PlayerHUD = nullptr;
	wallet = 0;
	endGoal = 100;
}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = Cast<APlayerController>(Controller);
	if (!PC || !IsLocallyControlled())
	{
		return;
	}

	// Setup HUD widgets
	if (PlayerHUDClass)
	{
		PlayerHUD = CreateWidget<UPlayerHUD>(PC, PlayerHUDClass);
	}

	if (MainMenuHUDClass)
	{
		MainMenuHUD = CreateWidget<UMainMenuHUD>(PC, MainMenuHUDClass);
		ShowMainMenu();
	}

	// Setup Enhanced Input
	if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}


void APlayerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PlayerHUD)
	{
		PlayerHUD->RemoveFromParent();
		PlayerHUD = nullptr;
	}

	Super::EndPlay(EndPlayReason);
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
	//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f);
	//if (bHit) DrawDebugPoint(GetWorld(), HitResult.ImpactPoint, 15.0f, FColor::Green, false, 2.0f);

	if (bHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitResult.GetActor()->GetName());

		// Check if we hit a Planting_Ground actor
		APlanting_Ground* PlantingGround = Cast<APlanting_Ground>(HitResult.GetActor());
		if (PlantingGround)
		{
			// Call SetWateredState on the hit Planting_Ground
			if (!PlantingGround->bIsWatered) {
				PlantingGround->SetWateredState();
				UE_LOG(LogTemp, Log, TEXT("Watered planting ground!"));
				return; // Exit after watering, don't try to spawn plant
			}
			else if (PlantingGround->bIsWatered && currentSeedAmount > 0)
			{

				FVector SpawnLocation = HitResult.ImpactPoint + (HitResult.ImpactNormal * 5.0f);

				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride =
					ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
					PlantClass,
					FTransform(SpawnLocation),
					SpawnParams
				);

				currentSeedAmount -= 1;
				PlayerHUD->UpdateSeedTracker(currentSeedAmount);


				UE_LOG(LogTemp, Log, TEXT("1 plant spawned."));

				if (SpawnedActor)
				{
					UE_LOG(LogTemp, Warning, TEXT("SPAWNED: %s"), *SpawnedActor->GetName());
					//DrawDebugSphere(GetWorld(), SpawnLocation, 25.0f, 12, FColor::Blue, false, 3.0f);

					ACarrot* SpawnedCarrot = Cast<ACarrot>(SpawnedActor);
					if (SpawnedCarrot)
					{
						PlantingGround->PlantedCarrots.Add(SpawnedCarrot);
					}

				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("FAILED TO SPAWN!"));
				}
			}
			else if (PlantingGround->bIsWatered && currentSeedAmount <= 0)
			{
				UE_LOG(LogTemp, Log, TEXT("Out of seeds!"));
				return;
			}
			
			if (!PlantClass)
			{
				UE_LOG(LogTemp, Error, TEXT("PlantClass is NOT assigned!"));
				return;
			}


			
		}

		// Check if we hit a Carrot actor
		if (ACarrot* hitCarrot = Cast<ACarrot>(HitResult.GetActor()))
		{
			if (hitCarrot->bIsFullGrown)
			{
				wallet = wallet + hitCarrot->SellAmount;

				if (IsValid(hitCarrot))
				{
					hitCarrot->Destroy();
					UE_LOG(LogTemp, Log, TEXT("Destroyed fully grown carrot!"));
				}

				if (PlayerHUD)
				{
					PlayerHUD->SetMoney(wallet);
					PlayerHUD->UpdateProgress(wallet/endGoal);
				}
			}
		}

		if (AShop* hitShop = Cast<AShop>(HitResult.GetActor()))
		{
			UE_LOG(LogTemp, Log, TEXT("Shop hit!"));
			hitShop->purchase(hitShop->shopItem, this);
		}
		
	}
}
void APlayerCharacter::SetUIOnlyInputMode()
{
	if (APlayerController* PC = GetController<APlayerController>())
	{
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
	}
}

void APlayerCharacter::SetGameOnlyInputMode()
{
	if (APlayerController* PC = GetController<APlayerController>())
	{
		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = false;
	}
}

void APlayerCharacter::ShowMainMenu()
{
	if (MainMenuHUD)
	{
		MainMenuHUD->StartButton->SetVisibility(ESlateVisibility::Visible);
		MainMenuHUD->ReplayButton->SetVisibility(ESlateVisibility::Collapsed);

		MainMenuHUD->AddToViewport();
		SetUIOnlyInputMode();
	}
}

void APlayerCharacter::ShowEndMenu()
{
	if (MainMenuHUD)
	{
		
		MainMenuHUD->EndScreen();
		MainMenuHUD->AddToViewport();
		PlayerHUD->RemoveFromParent();
		SetUIOnlyInputMode();
	}
}

void APlayerCharacter::HideMainMenu()
{
	if (MainMenuHUD)
	{
		MainMenuHUD->RemoveFromParent();
		PlayerHUD->AddToViewport();
		SetGameOnlyInputMode();
	}
}



