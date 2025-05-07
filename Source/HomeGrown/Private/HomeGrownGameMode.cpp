// Fill out your copyright notice in the Description page of Project Settings.


#include "HomeGrownGameMode.h"


void AHomeGrownGameMode::StartPlay()
{

    Super::StartPlay();


    check(GEngine != nullptr);

    // Display a debug message for five seconds. 
    // The -1 "Key" value argument prevents the message from being updated or refreshed.

    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Hello World, this is HomeGrown!"));
    UE_LOG(LogTemp, Warning, TEXT("StartPlay was called!"));

}
