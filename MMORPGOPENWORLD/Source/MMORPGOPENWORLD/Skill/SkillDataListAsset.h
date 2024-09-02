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
	void SetOwner(TObjectPtr<AActor> OwnerCS);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float CoolDown = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	TArray<FSkillStruct> SkillList;
};
