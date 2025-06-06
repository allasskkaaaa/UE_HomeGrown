#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuHUD.generated.h"

UCLASS()
class HOMEGROWN_API UMainMenuHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void StartGame();

	UFUNCTION(BlueprintCallable)
	void ExitGame();

	UFUNCTION(BlueprintCallable)
	void RestartGame();

	UFUNCTION(BlueprintCallable)
	void EndScreen();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* titleText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ReplayButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ExitButton;
};