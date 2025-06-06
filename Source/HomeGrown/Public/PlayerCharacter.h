#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h" // Needed for FInputActionValue
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;

class ACarrot;

UCLASS()
class HOMEGROWN_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Planting")
	TSubclassOf<ACarrot> PlantClass;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Input Actions and Mapping Context
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* InteractAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void LineTrace();
	void SpawnPlant(FVector spawnLocation);

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetUIOnlyInputMode();
	void SetGameOnlyInputMode();
	void ShowMainMenu();
	void ShowEndMenu();
	void HideMainMenu();

	// Player camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPlayerHUD> PlayerHUDClass;

	UPROPERTY()
	class UPlayerHUD* PlayerHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float wallet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float endGoal;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMainMenuHUD> MainMenuHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMainMenuHUD* MainMenuHUD;

};
