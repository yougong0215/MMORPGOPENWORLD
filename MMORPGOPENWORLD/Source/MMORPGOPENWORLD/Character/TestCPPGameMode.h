// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestCPPGameMode.generated.h"

UCLASS(minimalapi)
class ATestCPPGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void StartPlay() override;

	ATestCPPGameMode();
protected:
	// 매 프레임 호출되는 함수
	virtual void Tick(float DeltaTime) override;
	void UpdateDefaultPawnClass();
};



