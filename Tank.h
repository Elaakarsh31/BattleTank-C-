// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override; //called by the engine when tank takes the damage

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const; //return health percentage between 0 and 1

	FTankDelegate OnDeath;

	bool IsDead() const;

	float GetHealth(float Health);

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;
	
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MoveSpeed = 100.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DestroyDelay = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float RotateSpeed = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UParticleSystem* DestroyBlast = nullptr;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class USoundBase* DeathSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class USoundBase* EngineSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UCameraShake> DeathShake;

	FVector MoveDirection;
	FQuat RotationDirection;
	FTimerHandle Delay;

	class UTankTrack* LeftTrack = nullptr;
	class UTankTrack* RightTrack = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitialiseTracks(class UTankTrack* LeftTrackToSet, class UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void CalculateMoveInput(float Throttle);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void CalculateRotateInput(float Throttle);

	void Destruct();
	void Move();
	void Rotate();
};
