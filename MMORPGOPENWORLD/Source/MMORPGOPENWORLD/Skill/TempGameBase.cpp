// Fill out your copyright notice in the Description page of Project Settings.


#include "TempGameBase.h"
#include "TempCharacter.h"
#include "TempCharacterController.h"
#include "TempGameBase.h"

ATempGameBase::ATempGameBase()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATempCharacterController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/YOUGONG/TempCharacter.TempCharacter_C"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/YOUGONG/Controller.Controller_C"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}
