// Fill out your copyright notice in the Description page of Project Settings.


#include "Sound/SoundManager.h"

// Sets default values
ASoundManager::ASoundManager()
{

}

// Called when the game starts or when spawned
void ASoundManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASoundManager::OnBGM()
{
	BP_OnBGM();
}

