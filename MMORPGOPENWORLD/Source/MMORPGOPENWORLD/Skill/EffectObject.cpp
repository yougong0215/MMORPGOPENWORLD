// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectObject.h"
#include "NiagaraComponent.h"
#include <Components/BoxComponent.h>
#include "NiagaraFunctionLibrary.h"

// Sets default values
AEffectObject::AEffectObject()
{
	_isStart = false;
}

// Called when the game starts or when spawned
void AEffectObject::BeginPlay()
{
	Super::BeginPlay();
}

void AEffectObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_isStart == false)
		return;

	FVector ForwardVector = GetActorForwardVector();
	FVector MoveDirection = ForwardVector * 5 * DeltaTime;
	SetActorLocation(GetActorLocation() + MoveDirection);
}

// 플레이어에서 발사해야됨
void AEffectObject::Begin(FQuat dir, FVector Size)
{
	SetActorRotation(dir);
	BoxComponent->SetRelativeScale3D(Size);

	comp =  UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Skill.Effect, FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 60.0f));
	comp->Activate();
	_isStart = true;
}
