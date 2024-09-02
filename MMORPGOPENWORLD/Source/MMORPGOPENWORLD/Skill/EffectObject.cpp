// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectObject.h"
#include "NiagaraComponent.h"
#include <Components/BoxComponent.h>
#include "NiagaraFunctionLibrary.h"

// Sets default values
AEffectObject::AEffectObject()
{

}

// Called when the game starts or when spawned
void AEffectObject::BeginPlay()
{
	Super::BeginPlay();
}

void AEffectObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SetActorLoac
}

// 플레이어에서 발사해야됨
void AEffectObject::Begin(FQuat dir, FVector Size)
{
	SetActorRotation(dir);
	BoxComponent->SetRelativeScale3D(Size);
}

