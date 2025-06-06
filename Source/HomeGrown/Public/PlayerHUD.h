#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

UCLASS()
class HOMEGROWN_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetMoney(float currentMoney);

	UFUNCTION(BlueprintCallable)
	void UpdateProgress(float currentProgress);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* MoneyTracker;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* MoneyBar;
};