// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankWheels.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankWheels : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Spin(float RotationSpeed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegreesPerSecond = 30;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float Max = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinRotationDegrees = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxRotationDegrees = 40;

	float NewRotation;
	FQuat RotationDirection;
};
