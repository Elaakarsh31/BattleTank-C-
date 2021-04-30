// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NameTypes.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BattleTankGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UBattleTankGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void LoadNextLevel();

private:

	TArray<FName> Levels;
	int32 CurrentLevel = 0;
};


