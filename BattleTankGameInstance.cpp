// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UBattleTankGameInstance::LoadNextLevel()
{
	Levels = { "City", "Forest", "END" };
	if (CurrentLevel + 1 < Levels.Num())
	{
		CurrentLevel++;
		UGameplayStatics::OpenLevel(this, Levels[CurrentLevel]);
	}
}