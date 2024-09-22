// Fill out your copyright notice in the Description page of Project Settings.


#include "Server/MenuWidget.h"

void UMenuWidget::Setup()
{
	this->AddToViewport();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();

		FInputModeUIOnly InputModeData;
		InputModeData.SetWidgetToFocus(this->TakeWidget());
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		if (PlayerController)
		{
			PlayerController->SetInputMode(InputModeData);

			PlayerController->bShowMouseCursor = true;

		}
	}

}

void UMenuWidget::Teardown()
{
	this->RemoveFromViewport();

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->bShowMouseCursor = true;
		}
	}
}

void UMenuWidget::SetMenuInterface(IMenuInterface* InMenuInterface)
{
	this->MenuInterface = InMenuInterface;
}