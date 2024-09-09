// Fill out your copyright notice in the Description page of Project Settings.

#include "TempCharacterController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SkillDataListAsset.h"
#include "TempCharacter.h"

void ATempCharacterController::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ATempCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &ATempCharacterController::Fire);

	}
}

void ATempCharacterController::Fire()
{
	Skill->SetFire(this, GetWorld());
}
