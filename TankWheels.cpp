// Fill out your copyright notice in the Description page of Project Settings.


#include "TankWheels.h"

void UTankWheels::BeginPlay()
{
	Super::BeginPlay();
	
}
void UTankWheels::Spin(float RotationSpeed)
{
	float Spin = RotationSpeed * MaxDegreesPerSecond * GetWorld()->GetTimeSeconds();
	float RotateAmount = FMath::Clamp(Spin, -1.f, 1.f);
	AddLocalRotation(FRotator(RotateAmount* Max, 0.f, 0.f));
}