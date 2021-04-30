// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankWheels.h"
#include "SpawnPointComponent.h"
#include "SprungWheel.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

}



void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);

	Current = CurrentThrottle;
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	auto TankWheel = GetTankWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}

	for (AWheel* Wheel : TankWheel)
	{
		Wheel->AddSpinForce(CurrentThrottle);
	}

}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPointComponent>(Child);
		if (!SpawnPointChild) continue;

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;

		ResultArray.Add(SprungWheel);
	}

	return ResultArray;
}

TArray<AWheel*> UTankTrack::GetTankWheels() const
{
	TArray<AWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPointComponent>(Child);
		if (!SpawnPointChild) continue;

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto Wheel = Cast<AWheel>(SpawnedChild);
		if (!Wheel) continue;

		ResultArray.Add(Wheel);
	}

	return ResultArray;
}

void UTankTrack::DestroyWheels()
{
	for (AWheel* wheel : GetTankWheels())
	{
		if (!wheel) continue;
		wheel->Destroy();
	}
}