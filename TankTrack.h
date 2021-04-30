// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include"Wheel.h"
#include "TankWheels.h"
#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Track is used for maximum force to drive the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000;    //Max force in newtons

	void DestroyWheels();

private:
	UTankTrack();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;
	void DriveTrack(float CurrentThrottle);

	TArray<class ASprungWheel*> GetWheels() const;
	TArray<class AWheel*> GetTankWheels() const;
	class ATank* PlayerTank = nullptr;

	float Current = 0;
};
