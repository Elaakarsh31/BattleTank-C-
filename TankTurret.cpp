// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Components/SceneComponent.h"

void UTankTurret::Rotate(float RotationSpeed)
{
	RotationSpeed = FMath::Clamp<float>(RotationSpeed, -1, 1);
	auto RotationChange = RotationSpeed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	auto NewRotation = GetRelativeRotation().Yaw + RotationChange;
	
	SetRelativeRotation(FRotator(0, NewRotation, 0));
}