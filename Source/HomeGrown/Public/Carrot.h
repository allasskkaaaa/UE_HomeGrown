#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Carrot.generated.h"

UCLASS()
class HOMEGROWN_API ACarrot : public AActor
{
    GENERATED_BODY()

public:
    ACarrot();

    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* CarrotMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantity",
    meta = (ClampMin = "0"))
    int32 Quantity = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth")
    bool bIsFullGrown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth",
        meta = (ClampMin = "0.1"))
    float GrowthDuration = 10.0f;  // Time in seconds to reach full size

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Growth")
    float CurrentGrowthTime = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth",
        meta = (ClampMin = "0.1"))
    float MaxScale = 1.0f;  // Maximum size multiplier

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth",
        meta = (ClampMin = "0.0", ClampMax = "1.0", DisplayName = "Hydration Level", UIMin = 0.0, UIMax = 1.0))
    float Hydration = 0.0f;  

    // Economic Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economics",
        meta = (ClampMin = "0", DisplayName = "Sell Price"))
    int32 SellAmount = 10; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Economics",
        meta = (ClampMin = "0", DisplayName = "Purchase Cost"))
    int32 CostAmount = 5;  

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
};