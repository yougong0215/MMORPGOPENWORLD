// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ABCharacterStatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MMORPGOPENWORLD_API UABCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UABCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FORCEINLINE float GetMaxHp() { return MaxHp; }
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }

	void SetHp(float NewHp);
	float ApplyDamage(float InDamage);

	// 플레이어를 일정 시간 동안 움직이지 못하게 하는 함수
	void DisableMovement();

	// 3초 후에 플레이어의 움직임을 다시 허용하는 함수
	void EnableMovement();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Stat)
	float MaxHp;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = Stat)
	float CurrentHp;

	FTimerHandle MovementDisableTimerHandle;
		
};
