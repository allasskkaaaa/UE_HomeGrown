// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shop.generated.h"

class ACarrot;
class APlayerCharacter;
class APlayerHUD;

UCLASS()
class HOMEGROWN_API AShop : public AActor
{
	GENERATED_BODY()
	
public:	


public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TSubclassOf<ACarrot> shopItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	int32 shopStockPrice = 2;

	void purchase(TSubclassOf<ACarrot> item, APlayerCharacter* player);

};
