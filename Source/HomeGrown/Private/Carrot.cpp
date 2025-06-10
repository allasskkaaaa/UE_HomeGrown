// Fill out your copyright notice in the Description page of Project Settings.

#include "Carrot.h"

// Sets default values
ACarrot::ACarrot()
{
    // Set this actor to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Initialize mesh component (name matches header)
    CarrotMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarrotMeshComponent"));
    SetRootComponent(CarrotMeshComponent);
    CarrotMeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));

    // Initialize default values
    SellAmount = 10;
    CostAmount = 5;
    bIsFullGrown = false;
    bIsWatered = true;
}

// Called when the game starts or when spawned
void ACarrot::BeginPlay()
{
    Super::BeginPlay();

    CarrotMeshComponent->SetWorldScale3D(FVector(StartScale));
    CurrentGrowthTime = 0.0f;

}

// Called every frame
void ACarrot::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //Scales the carrot if not already full grown and watered
    if (CurrentGrowthTime < GrowthDuration && bIsWatered)
    {
        // Update growth timer
        CurrentGrowthTime += DeltaTime;

        // Calculate growth progress (0 to 1)
        float GrowthProgress = FMath::Clamp(CurrentGrowthTime / GrowthDuration, 0.0f, 1.0f);

        // Apply smooth scaling (optional curve)
        float ScaleValue = GrowthProgress * MaxScale;

        // Set new scale (uniform scaling)
        CarrotMeshComponent->SetWorldScale3D(FVector(ScaleValue));

    }
    else if (CurrentGrowthTime >= GrowthDuration)
    {
        bIsFullGrown = true;
    }
    

}