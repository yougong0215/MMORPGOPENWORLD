// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/GroundObject.h"

// Sets default values
AGroundObject::AGroundObject()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGroundObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGroundObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGroundObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

