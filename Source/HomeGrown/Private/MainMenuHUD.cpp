#include "MainMenuHUD.h"
#include "Components/Button.h"
#include "Components/Textblock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerCharacter.h"

class APlayerCharacter;

void UMainMenuHUD::NativeConstruct()
{
    Super::NativeConstruct(); 

    // Bind button events
    if (StartButton) 
    {
        StartButton->OnClicked.AddDynamic(this, &UMainMenuHUD::StartGame);
    }

    if (ExitButton) 
    {
        ExitButton->OnClicked.AddDynamic(this, &UMainMenuHUD::ExitGame);
    }

    if (ReplayButton)
    {
        ReplayButton->OnClicked.AddDynamic(this, &UMainMenuHUD::RestartGame);
    }
    
}

void UMainMenuHUD::StartGame()
{

    if (APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
    {
        Player->HideMainMenu();
    }
}

void UMainMenuHUD::EndScreen()
{
    if (APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
    {
        StartButton->SetVisibility(ESlateVisibility::Collapsed);
        ReplayButton->SetVisibility(ESlateVisibility::Visible);

        FText newText = NSLOCTEXT("MyNamespace", "VictoryTitle", "You are out of debt!");
        titleText->SetText(newText);
    }

}

void UMainMenuHUD::RestartGame()
{
    UGameplayStatics::OpenLevel(this, FName("Level"));

}

void UMainMenuHUD::ExitGame()
{
    UKismetSystemLibrary::QuitGame(
        GetWorld(),
        nullptr,
        EQuitPreference::Quit,
        false
    );
}