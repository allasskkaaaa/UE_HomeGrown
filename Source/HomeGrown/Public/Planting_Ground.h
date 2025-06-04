// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Planting_Ground.generated.h"

UCLASS()
class HOMEGROWN_API APlanting_Ground : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlanting_Ground();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* GroundMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground Properties")
	UMaterialInstance* DryMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground Properties")
	UMaterialInstance* WateredMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground Properties")
	bool bIsWatered;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground Properties", meta = (ClampMin = "0", ClampMax = "10"))
	float WaterLevel;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle WaterTimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetWateredState();
	void EndWatering();
};
