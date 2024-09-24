// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectObject.h"
#include "NiagaraComponent.h"
#include <Components/BoxComponent.h>
#include "NiagaraFunctionLibrary.h"

// Sets default values
AEffectObject::AEffectObject()
{
	//_isStart = false;
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
	FVector MoveDirection = ForwardVector * 1200 * DeltaTime;
	SetActorLocation(GetActorLocation() + MoveDirection);
	comp->AddRelativeLocation(MoveDirection);
}

// 플레이어에서 발사해야됨
void AEffectObject::Begin(TObjectPtr<AActor> OwnerCS, FSkillStruct _skill, UWorld* _world)
{
	Skill = _skill;

	FRotator CurrentRotation = OwnerCS->GetActorRotation();
	FVector location = OwnerCS->GetActorLocation();

	CurrentRotation.Yaw += Skill.BulletRange;


	SetActorRotation(CurrentRotation);
	//BoxComponent->SetRelativeScale3D(Skill.BulletSize * FVector::One());
	SetActorLocation(location);

	
	if (Skill.Effect)
	{
		comp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(_world, Skill.Effect, location + FVector(0,0,60));
		comp->SetWorldRotation(CurrentRotation);
		comp->SetWorldScale3D(FVector(2.0f));
		comp->SetVisibility(true);
		comp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
		// comp->Activate(); // 일반적으로 필요하지 않음

		// 이펙트가 생성되지 않았을 경우 에러 처리
		if (!comp)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn Niagara system"));
		}
	}


	_isStart = true;
}

void AEffectObject::OverlapedObject(AActor* OverlapedObject)
{
	if (Owner != OverlapedObject)
	{
		// 내가 아니면 데미지 판정
	}
}
