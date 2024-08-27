// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MPSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class MMORPGOPENWORLD_API UMPSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UMPSaveGame();

public:
	UPROPERTY()
	int32 Gold;

	UPROPERTY()
	int32 Diamond;

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	int32 Hero;
};