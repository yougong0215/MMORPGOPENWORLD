// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TempCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class MMORPGOPENWORLD_API ATempCharacterController : public APlayerController
{
	GENERATED_BODY()
	
	// To add mapping context
	virtual void BeginPlay();

public:
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	void Fire();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkillDataListAsset> Skill;

};
