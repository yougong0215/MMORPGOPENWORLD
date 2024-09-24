// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillData.generated.h"
/**
 * 
 */
class MMORPGOPENWORLD_API SkillData
{
public:
	SkillData();
	~SkillData();
};

USTRUCT(Atomic, BlueprintType)
struct FSkillStruct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Naigara)
	TObjectPtr<class UNiagaraSystem> Effect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float BulletDamage = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float BulletSpeed = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float BulletRange = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float BulletSize = 1.0f;


};
