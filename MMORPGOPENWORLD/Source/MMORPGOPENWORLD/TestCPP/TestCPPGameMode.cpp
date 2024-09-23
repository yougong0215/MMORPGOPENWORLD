// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestCPPGameMode.h"
#include "TestCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestCPPGameMode::ATestCPPGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/BasicCharacter"));

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}