// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthPack.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Tank.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AHealthPack::AHealthPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	HealthPack = CreateDefaultSubobject<UStaticMeshComponent>("HealthPack");
	BoxCollision->SetCollisionProfileName("Trigger");
	BoxCollision->InitBoxExtent(FVector(20, 20, 20));

	RootComponent = BoxCollision;
	HealthPack->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AHealthPack::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AHealthPack::OnOverlapBegin);
}

// Called every frame
void AHealthPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthPack::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		ATank* PlayerTank = Cast<ATank>(OtherActor);
		if (PlayerTank)
		{
			float CurrentHealth = 0;
			auto Health = PlayerTank->GetHealth(CurrentHealth);
			if (Health <= 90)
			{
				UGameplayStatics::SpawnSoundAtLocation(this, PickUpSound, GetActorLocation());
				CurrentHealth += 20;
				PlayerTank->GetHealth(CurrentHealth);
				Destroy();
			}
		}
	}
}
