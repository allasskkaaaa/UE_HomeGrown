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

    // Initialize default values (optional - already set in header)
    Hydration = 0.0f;
    SellAmount = 10;
    CostAmount = 5;
}

// Called when the game starts or when spawned
void ACarrot::BeginPlay()
{
    Super::BeginPlay();

    CarrotMeshComponent->SetWorldScale3D(FVector(0.f));
    CurrentGrowthTime = 0.0f;

}

// Called every frame
void ACarrot::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CurrentGrowthTime < GrowthDuration)
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

}