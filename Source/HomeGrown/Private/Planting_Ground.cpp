#include "Planting_Ground.h"
#include "Carrot.h"
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

//If the ground is not already watered, water it and all the crops on it. If it is watered, unwater it.
void APlanting_Ground::SetWateredState()
{
    if (!bIsWatered)
    {
        bIsWatered = true;
        WaterPlants();
        WaterLevel = 10;
        float dehydrationSpeed = FMath::Max(WaterLevel - PlantedCarrots.Num(), 1); //The more carrots there are, the more it subtracts from the dehydration speed (Default 10)

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
                dehydrationSpeed,
                false
            );
        }
    }
    else
    {
        UnWaterPlants();
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

//Sets all the carrots bIsWatererd bool to true
void APlanting_Ground::WaterPlants()
{
    for (int32 i = PlantedCarrots.Num() - 1; i >= 0; --i)
    {
        if (!IsValid(PlantedCarrots[i]))
        {
            PlantedCarrots.RemoveAt(i);
            UE_LOG(LogTemp, Log, TEXT("Removing invalid carrot"));
        }
    }

    for (ACarrot* Carrot : PlantedCarrots)
    {
        Carrot->bIsWatered = true;
        UE_LOG(LogTemp, Log, TEXT("Watered plant"));
    } 
}

//Sets all the carrots bIsWatererd bool to false
void APlanting_Ground::UnWaterPlants() 
{
    for (int32 i = PlantedCarrots.Num() - 1; i >= 0; --i)
    {
        if (!IsValid(PlantedCarrots[i]))
        {
            PlantedCarrots.RemoveAt(i);
            UE_LOG(LogTemp, Log, TEXT("Removing invalid carrots"));
        }
    }

    for (ACarrot* Carrot : PlantedCarrots)
    {
        Carrot->bIsWatered = false;
        UE_LOG(LogTemp, Log, TEXT("Unwatered plant"));
    }
}
