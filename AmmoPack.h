// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoPack.generated.h"

UCLASS()
class BATTLETANK_API AAmmoPack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoPack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* CapsuleCollision = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* AmmoPack = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float Radius = 50;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float Height = 100;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class USoundBase* PickUpSound = nullptr;

	class UTankAimingComponent* Rounds = nullptr;
	class AProjectile* Projectile = nullptr;
};
