// Fill out your copyright notice in the Description page of Project Settings.

#include "AmmoPack.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Projectile.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AAmmoPack::AAmmoPack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	AmmoPack = CreateDefaultSubobject<UStaticMeshComponent>("Ammo");
	CapsuleCollision->SetCollisionProfileName("Trigger");
	RootComponent = CapsuleCollision;
	AmmoPack->SetupAttachment(RootComponent);

	CapsuleCollision->InitCapsuleSize(Radius, Height);
}

// Called when the game starts or when spawned
void AAmmoPack::BeginPlay()
{
	Super::BeginPlay();
	CapsuleCollision->OnComponentBeginOverlap.AddDynamic(this, &AAmmoPack::OnOverlapBegin);
}

// Called every frame
void AAmmoPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAmmoPack::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		Projectile = Cast<AProjectile>(OtherActor);
		if (Projectile != nullptr)
		{
			return;
		}
		ATank* PlayerTank = Cast<ATank>(OtherActor);
		Rounds = PlayerTank->FindComponentByClass<UTankAimingComponent>();
		if (Rounds)
		{
			int32 Ammo = 0;
			auto RoundsLeft = Rounds->GetRoundsLeft(Ammo);
			if (RoundsLeft < 20)
			{
				UGameplayStatics::SpawnSoundAtLocation(this, PickUpSound, GetActorLocation());
				Ammo += 5;
				Rounds->GetRoundsLeft(Ammo);
				Destroy();
			}
		}
	}
}