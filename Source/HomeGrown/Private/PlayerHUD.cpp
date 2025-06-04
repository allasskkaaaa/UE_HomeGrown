#include "PlayerHUD.h"
#include "Components/Textblock.h"

void UPlayerHUD::SetMoney(float currentMoney)
{
    if (MoneyTracker)
    {
        FText MoneyText = FText::Format(NSLOCTEXT("Game", "MoneyFormat", "${0}"),FText::AsNumber(currentMoney));

        MoneyTracker->SetText(MoneyText); // Set the text
    } 
}