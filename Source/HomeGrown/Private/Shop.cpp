// Fill out your copyright notice in the Description page of Project Settings.

#include "Shop.h"
#include "PlayerCharacter.h"
#include "Carrot.h"
#include "PlayerHUD.h"


// Sets default values
AShop::AShop()
{

}

//Adds to the amount of seeds the player has
void AShop::purchase(TSubclassOf<ACarrot> item, APlayerCharacter* player)
{
	ACarrot* carrot = item->GetDefaultObject<ACarrot>();


	if (player->wallet < carrot->CostAmount) //If the player doesn't have enough money to purchase the item, immediately return
	{
		UE_LOG(LogTemp, Log, TEXT("Not enough money to buy"));
		return;
	}

	if (item)
	{
		player->currentSeedAmount += 1;
		player->wallet -= carrot->CostAmount; //Subtract the cost of the item from the wallet
		player->PlayerHUD->UpdateSeedTracker(player->currentSeedAmount); //Set the UI seed amount to the new value
		player->PlayerHUD->SetMoney(player->wallet); //Set the UI seed amount to the new value
		player->PlayerHUD->UpdateProgress(player->wallet / player->endGoal); //Set the UI progress amount to the new value
		UE_LOG(LogTemp, Log, TEXT("Carrot has been purchased!"));
	}

}

