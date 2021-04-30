// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankTrack.h"
#include "Sound/SoundBase.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "BattleTankGameModeBase.h"
#include "Components/SceneComponent.h"
#include "Wheel.h"
#include "SpawnPointComponent.h"
#include "Engine/World.h"

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth/(float)StartingHealth;
}

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}



// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
	UGameplayStatics::SpawnSoundAtLocation(this, EngineSound, GetActorLocation());
}

bool ATank::IsDead() const
{
	return CurrentHealth <= 0;
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
	Rotate();
}

void ATank::Destruct()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, DestroyBlast, GetActorLocation());
	UGameplayStatics::SpawnSoundAtLocation(this, DeathSound, GetActorLocation());
	Destroy();
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->DestroyWheels();
	RightTrack->DestroyWheels();
}

float ATank::GetHealth(float Health)
{
	CurrentHealth += Health;
	return CurrentHealth;
}

void ATank::InitialiseTracks(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet || !RightTrackToSet)) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void ATank::CalculateMoveInput(float Throttle)
{
	MoveDirection = FVector(Throttle * MoveSpeed, 0, 0);
}

void ATank::CalculateRotateInput(float Throttle)
{
	float RotateAmnt = Throttle * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmnt, 0);
	RotationDirection = FQuat(Rotation);

}

void ATank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void ATank::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
	
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) 
{
	int32 Damage = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(Damage, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		ABattleTankGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ABattleTankGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		OnDeath.Broadcast();
		GetWorld()->GetTimerManager().SetTimer(Delay, this, &ATank::Destruct, DestroyDelay);
	}
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathShake);

	return DamageToApply;
}
