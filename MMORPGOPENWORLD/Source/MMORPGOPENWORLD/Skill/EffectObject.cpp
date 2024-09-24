// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectObject.h"
#include "NiagaraComponent.h"
#include <Components/BoxComponent.h>
#include "NiagaraFunctionLibrary.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AEffectObject::AEffectObject()
{
	comp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffect"));
	SetRootComponent(comp);
	bReplicates = true;            // 오브젝트 복제 설정
	bNetLoadOnClient = true;       // 클라이언트에서 로드 허용
	SetReplicateMovement(true);
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

	if (!comp)
		return;

	FVector ForwardVector = GetActorForwardVector();
	FVector MoveDirection = ForwardVector * 1200 * DeltaTime;
	SetActorLocation(GetActorLocation() + MoveDirection);

	CurrentLocation = GetActorLocation();

	if (comp && comp->IsValidLowLevel())
		comp->AddRelativeLocation(MoveDirection);
}

void AEffectObject::Begin(TObjectPtr<AActor> OwnerCS, FSkillStruct _skill, UWorld* _world)
{
	Skill = _skill;

	FRotator CurrentRotation = OwnerCS->GetActorRotation();
	FVector location = OwnerCS->GetActorLocation();

	CurrentRotation.Yaw += Skill.BulletRange;


	SetActorRotation(CurrentRotation);
	SetActorLocation(location);


	if (Skill.Effect)
	{
		comp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(_world, Skill.Effect, location + FVector(0, 0, 60));
		comp->SetWorldRotation(CurrentRotation);
		comp->SetWorldScale3D(FVector(2.0f));
		comp->SetVisibility(true);
		comp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

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

	}
}

void AEffectObject::OnRep_Location()
{
	SetActorLocation(CurrentLocation);
}

void AEffectObject::OnRep_Skill()
{
	if (comp)
	{
		comp->SetAsset(Skill.Effect);
		// 나이아가라 효과를 재생
		comp->Activate();
		// 필요에 따라 다른 스킬 관련 효과 추가
	}
}

void AEffectObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEffectObject, Skill);
	DOREPLIFETIME(AEffectObject, CurrentLocation);
}