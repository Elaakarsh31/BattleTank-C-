// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UAITrack;
class UTankTrack;
class UTankWheels;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void TurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void AIInitialise(UAITrack* LeftTrackToSet, UAITrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	float UpdateTreadUVs(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	float TurnLeftTreadUVs(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	float TurnRightTreadUVs(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Effects")
	void SetupEngineNoise();

	UFUNCTION(BlueprintCallable, Category = "Effects")
	float EnginePitchHandler(float Forward, float Turning);

	UFUNCTION(BlueprintCallable, Category = "Effects")
	void SetPitch(float Pitch);

	float PositionOffset;
	float TurnOffset;

	float UVOffsetR = 0;

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	UAITrack* AILeftTrack = nullptr;
	UAITrack* AIRightTrack = nullptr;

	class UAudioComponent* Engine = nullptr;

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankWheels* TankWheel = nullptr;
	class ATank* Tank = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float SpeedForwardMax = 100;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float TreadLength = 1522.20;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float TreadUVTiles = 25;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float RotationSpeed = 10;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class USoundBase* EngineSound = nullptr;

	float OffsetL = 0;
	float OffsetR = 0;
	FQuat RotationDirection;

	UPROPERTY(EditAnywhere, Category = "Setup")
	int TreadRight = -1;
	UPROPERTY(EditAnywhere, Category = "Setup")
	int TreadLeft = 1;

};
