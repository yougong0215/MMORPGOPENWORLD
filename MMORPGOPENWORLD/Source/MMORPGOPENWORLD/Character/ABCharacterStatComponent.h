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

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Stat)
	float MaxHp;

	UPROPERTY(Transient, VisibleDefaultsOnly, Category = Stat)
	float CurrentHp;
		
};
