// Fill out your copyright notice in the Description page of Project Settings.

#include "Wheel.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "TankWheels.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
AWheel::AWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("WheelConstraint"));
	SetRootComponent(WheelConstraint);

	Wheel = CreateDefaultSubobject<UTankWheels>(FName("Wheel"));
	Wheel->SetupAttachment(WheelConstraint);

	/*Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(WheelConstraint);

	SphereWheel = CreateDefaultSubobject<USphereComponent>(FName("SphereWheel"));
	SphereWheel->SetupAttachment(Axle);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);*/

}

// Called when the game starts or when spawned
void AWheel::BeginPlay()
{
	Super::BeginPlay();
	//SetupConstraint();
}

void AWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }

	WheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, SphereWheel, NAME_None);
}

void AWheel::AddSpinForce(float Throttle)
{
	Wheel->Spin(Throttle);
}

void AWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
