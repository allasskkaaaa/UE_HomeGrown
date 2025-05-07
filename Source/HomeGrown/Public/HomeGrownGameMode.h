// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HomeGrownGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HOMEGROWN_API AHomeGrownGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void StartPlay() override;
};
