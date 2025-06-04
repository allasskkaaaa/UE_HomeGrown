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

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* MoneyTracker;

};