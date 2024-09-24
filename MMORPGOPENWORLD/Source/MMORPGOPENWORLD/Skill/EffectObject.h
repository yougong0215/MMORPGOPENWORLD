// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollisionObject.h"
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
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Begin(TObjectPtr<AActor> OwnerCS, FSkillStruct _skill, UWorld* _world);

	virtual void OverlapedObject(AActor* OverlapedObject) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BX)
	TObjectPtr<class UBoxComponent> BoxComponent;
	TObjectPtr<class UNiagaraComponent> comp;
	
	UPROPERTY(ReplicatedUsing = OnRep_Skill) // Replication 설정
	FSkillStruct Skill;

	UFUNCTION()
	void OnRep_Location();

	bool _isStart = false;
public:
	// OnRep 함수 정의
	UFUNCTION()
	void OnRep_Skill();

	UPROPERTY(ReplicatedUsing = OnRep_Location)
	FVector CurrentLocation;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
