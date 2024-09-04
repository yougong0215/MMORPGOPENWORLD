// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CollisionObject.h"
#include "SkillData.h"
#include "EffectObject.generated.h"


UCLASS()
class MMORPGOPENWORLD_API AEffectObject : public ACollisionObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffectObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Begin(FQuat dir, FVector Size);

	//virtual void OverlapedObject(AActor* OverlapedObject) override;
public:
	TObjectPtr<class UBoxComponent> BoxComponent;
	TObjectPtr<class UNiagaraComponent> comp;
	FSkillStruct Skill;

	bool _isStart = false;
};
