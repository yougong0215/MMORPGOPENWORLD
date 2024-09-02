// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionObject.h"

// Sets default values
ACollisionObject::ACollisionObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ACollisionObject::SetUP(TObjectPtr<AActor> OwnerCS)
{
	this->Owner = OwnerCS;
}

void ACollisionObject::OverlapedObject(AActor* OverlapedObject)
{
	if (Owner != OverlapedObject)
	{
		// 뭔가 넣어주기
	}
}

