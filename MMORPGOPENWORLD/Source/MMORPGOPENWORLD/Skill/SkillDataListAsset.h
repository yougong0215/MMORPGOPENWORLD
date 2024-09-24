// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SkillData.h"
#include "SkillDataListAsset.generated.h"

/**
 * 
 */
UCLASS()
class MMORPGOPENWORLD_API USkillDataListAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	void SetFire(TObjectPtr<AActor> OwnerCS, UWorld* _world);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BP)
	TSubclassOf<class AEffectObject> EffectObjectBPClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float CoolDown = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	TArray<FSkillStruct> SkillList;


};
