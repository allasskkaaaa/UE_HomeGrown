#include "Planting_Ground.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"

APlanting_Ground::APlanting_Ground()
{
    PrimaryActorTick.bCanEverTick = true;

    GroundMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GroundMeshComponent"));
    SetRootComponent(GroundMeshComponent);
    GroundMeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));

    // Load default cube mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube"));
    if (CubeMeshAsset.Succeeded())
    {
        GroundMeshComponent->SetStaticMesh(CubeMeshAsset.Object);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Could not find default cube mesh!"));
    }

    WateredMaterial = nullptr;
    DryMaterial = nullptr;
    bIsWatered = false;
    WaterLevel = 0.0f;

}

void APlanting_Ground::BeginPlay()
{
    Super::BeginPlay();
}

void APlanting_Ground::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void APlanting_Ground::SetWateredState()
{
    if (!bIsWatered)
    {
        bIsWatered = true;
        WaterLevel = 10;

        if (GroundMeshComponent)
        {
            // Create or get dynamic material instance
            UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(GroundMeshComponent->GetMaterial(0));

            // If not already dynamic, create one
            if (WateredMaterial) {
                GroundMeshComponent->SetMaterial(0, WateredMaterial);
            }

            GetWorld()->GetTimerManager().SetTimer(
                WaterTimerHandle,
                this,
                &APlanting_Ground::EndWatering,
                WaterLevel,
                false
            );
        }
    }
    else
    {
        bIsWatered = false;
        WaterLevel = 0;

        if (GroundMeshComponent)
        {
            // Create or get dynamic material instance
            UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(GroundMeshComponent->GetMaterial(0));

            // If not already dynamic, create one
            if (WateredMaterial) {
                GroundMeshComponent->SetMaterial(0, DryMaterial);
            }
        }
    }
}

void APlanting_Ground::EndWatering()
{
    SetWateredState();
    UE_LOG(LogTemp, Log, TEXT("Water timer completed"));
}