// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollisionObject.generated.h"

UCLASS()
class MMORPGOPENWORLD_API ACollisionObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollisionObject();

public:

	virtual void SetUP(TObjectPtr<AActor> OwnerCS);

	// Called every frame
	UFUNCTION(BlueprintCallable, Category = "Func")
	virtual void OverlapedObject(AActor* OverlapedObject);

public:
	TObjectPtr<AActor> Owner;
};
