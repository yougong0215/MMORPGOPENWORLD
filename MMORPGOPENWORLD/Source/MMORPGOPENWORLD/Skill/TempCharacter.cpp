// Fill out your copyright notice in the Description page of Project Settings.


#include "TempCharacter.h"
#include "SkillDataListAsset.h"


// Sets default values
ATempCharacter::ATempCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATempCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATempCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input

//void ATempCharacter::Fire(const FInputActionValue& Value)
//{
//	Skill->SetFire(this);
//}


