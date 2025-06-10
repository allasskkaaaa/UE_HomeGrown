#include "PlayerHUD.h"
#include "Components/Textblock.h"
#include "Components/ProgressBar.h"
#include "PlayerCharacter.h"

//Update the money counter UI
void UPlayerHUD::SetMoney(float currentMoney)
{
    if (MoneyTracker)
    {
        FText NewText = FText::Format(NSLOCTEXT("Game", "MoneyFormat", "${0}"),FText::AsNumber(currentMoney));

        MoneyTracker->SetText(NewText); // Set the text

        UE_LOG(LogTemp, Log, TEXT("Updated money UI"));
    } 
}

//Update the seed counter UI
void UPlayerHUD::UpdateSeedTracker(float currentSeedAmount)
{
    if (SeedTracker)
    {
        FText NewText = FText::Format(NSLOCTEXT("Game", "MoneyFormat", "{0}"), FText::AsNumber(currentSeedAmount));

        SeedTracker->SetText(NewText); // Set the text
        UE_LOG(LogTemp, Log, TEXT("Updated seed UI"));
    }
}

//Update the debt progress bar UI
void UPlayerHUD::UpdateProgress(float currentProgress)
{
    if (MoneyBar)
    {

        MoneyBar->SetPercent(currentProgress);

        if (MoneyBar->GetPercent() >= 1)
        {
            //Win game!
            if (APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
            {
                Player->ShowEndMenu();
            }
        }
    }
    
    
}