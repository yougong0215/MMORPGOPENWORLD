// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ABCharacterStatComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UABCharacterStatComponent::UABCharacterStatComponent()
{
	MaxHp = 200.f;
	CurrentHp = MaxHp;
}


// Called when the game starts
void UABCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHp(MaxHp);
}

void UABCharacterStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, MaxHp);
}

float UABCharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	if (CurrentHp <= KINDA_SMALL_NUMBER)
		return 0;

	SetHp(PrevHp - ActualDamage);

	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		// 플레이어 움직임 비활성화
		DisableMovement();

		// 3초 후에 움직임 활성화
		GetWorld()->GetTimerManager().SetTimer(MovementDisableTimerHandle, this, &UABCharacterStatComponent::EnableMovement, 3.0f, false);
	}

	return ActualDamage;
}

void UABCharacterStatComponent::DisableMovement()
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		OwnerCharacter->GetCharacterMovement()->DisableMovement();
	}
}

void UABCharacterStatComponent::EnableMovement()
{
	// 캐릭터의 움직임을 다시 활성화
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (OwnerCharacter)
	{
		OwnerCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		CurrentHp = MaxHp;
	}
}
