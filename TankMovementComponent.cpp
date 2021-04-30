// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "AITrack.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "GameFramework/Actor.h"
#include "TankWheels.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet || RightTrackToSet)) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::AIInitialise(UAITrack* LeftTrackToSet, UAITrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet || !RightTrackToSet)) { return; }
	AILeftTrack = LeftTrackToSet;
	AIRightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardMovement = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardMovement); // throw value required to move in the direction of player tank
	auto RotationThrow = FVector::CrossProduct(TankForward, AIForwardMovement).Z;

	//IntendTurnRight(RotationThrow);
	//IntendMoveForward(ForwardThrow);

	MoveForward(ForwardThrow);
	TurnRight(RotationThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::MoveForward(float Throw)
{
	GetOwner()->AddActorLocalOffset(FVector(Throw* 50 , 0, 0));
}

void UTankMovementComponent::TurnRight(float Throw)
{
	float RotateAmnt = Throw* RotationSpeed * GetWorld()->GetTimeSeconds();
	FRotator Rotation = FRotator(0, RotateAmnt, 0);
	auto Rotate = FQuat(Rotation);
	GetOwner()->AddActorLocalRotation(Rotate);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

float UTankMovementComponent::UpdateTreadUVs(float Throw)
{
	PositionOffset = Throw * SpeedForwardMax * GetWorld()->GetDeltaSeconds();
	OffsetL += PositionOffset;
	OffsetR += PositionOffset;
	auto Div = TreadLength / TreadUVTiles;

	float UVOffsetL = OffsetL / Div;

	return UVOffsetL;
}

float UTankMovementComponent::TurnLeftTreadUVs(float Throw)
{
	TurnOffset = Throw * SpeedForwardMax * GetWorld()->GetDeltaSeconds();
	OffsetL += PositionOffset + (TreadLeft * TurnOffset);

	auto Div = TreadLength / TreadUVTiles;
	float UVOffsetL = OffsetL / Div;

	return UVOffsetL;
}

float UTankMovementComponent::TurnRightTreadUVs(float Throw)
{
	TurnOffset = Throw * SpeedForwardMax * GetWorld()->GetDeltaSeconds();
	OffsetR += PositionOffset + (TreadRight * TurnOffset);

	auto Div = TreadLength / TreadUVTiles;
	UVOffsetR = OffsetR / Div;

	return UVOffsetR;
}

void UTankMovementComponent::SetupEngineNoise()
{
	Tank = Cast<ATank>(GetOwner());
	if (Tank != nullptr)
	{
		Engine = UGameplayStatics::SpawnSoundAttached(EngineSound, Tank->GetRootComponent());
	}
}

float UTankMovementComponent::EnginePitchHandler(float Forward, float Turning)
{
	float SpeedForward = FMath::Abs(Forward*10);
	float SpeedTurning = FMath::Abs(Turning * 10);
	auto Value = SpeedForward + SpeedTurning;
	
	return Value;
}

void UTankMovementComponent::SetPitch(float Pitch)
{
	auto pitch = Pitch;
	if (Engine != nullptr)
	{
		Engine->SetPitchMultiplier(pitch);
	}
}
