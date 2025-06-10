#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Carrot.generated.h"

class APlanting_Ground;

UCLASS()
class HOMEGROWN_API ACarrot : public AActor
{
    GENERATED_BODY()

public:
    ACarrot();

    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* CarrotMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components",
    meta = (ClampMin = "0"))
    int32 Quantity = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    bool bIsFullGrown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    bool bIsWatered; //Is updated when the ground is watered and when the ground dries out

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components",
        meta = (ClampMin = "0.1"))
    float GrowthDuration = 10.0f;  // Time in seconds to reach full size

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    float CurrentGrowthTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
    float SapSpeed = 1.0f; //How fast it takes water from the ground

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components",
        meta = (ClampMin = "0.1"))
    float MaxScale = 1.0f;  // Maximum size multiplier

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components",
        meta = (ClampMin = "0.1"))
    float StartScale = 0.2f;  // Minimum size multiplier

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components",
        meta = (ClampMin = "0", DisplayName = "Sell Price"))
    int32 SellAmount = 10; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components",
        meta = (ClampMin = "0", DisplayName = "Purchase Cost"))
    int32 CostAmount = 5;  

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    int32 itemAmount = 3;



protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
};