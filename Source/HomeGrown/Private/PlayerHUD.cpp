#include "PlayerHUD.h"
#include "Components/Textblock.h"
#include "Components/ProgressBar.h"
#include "PlayerCharacter.h"

void UPlayerHUD::SetMoney(float currentMoney)
{
    if (MoneyTracker)
    {
        FText MoneyText = FText::Format(NSLOCTEXT("Game", "MoneyFormat", "${0}"),FText::AsNumber(currentMoney));

        MoneyTracker->SetText(MoneyText); // Set the text
    } 
}

void UPlayerHUD::UpdateProgress(float currentProgress)
{
    if (MoneyBar)
    {

        MoneyBar->SetPercent(currentProgress);
    }
    
    if (MoneyBar->GetPercent() == 1)
    {
        //Win game!
        if (APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
        {
            Player->ShowEndMenu();
        }
    }
}