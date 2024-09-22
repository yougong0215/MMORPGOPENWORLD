// Fill out your copyright notice in the Description page of Project Settings.


#include "Server/ServerInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MainMenu.h"
#include "MenuWidget.h"

const static FName SESSION_NAME = TEXT("My Session Game");
UServerInstance::UServerInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));

	if (MenuBPClass.Class)
	{
		MenuClass = MenuBPClass.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));

	if (InGameMenuBPClass.Class)
	{
		InGameMenuClass = InGameMenuBPClass.Class;
	}
}

void UServerInstance::Init()
{
	Super::Init();
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (nullptr != Subsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Subsystem %s"), *Subsystem->GetSubsystemName().ToString());
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UServerInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UServerInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UServerInstance::OnFindSessionComplete);

			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			if (SessionSearch)
			{
				SessionSearch->bIsLanQuery = true;
				UE_LOG(LogTemp, Warning, TEXT("Starting Find Session"));
				SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Don't Found Subsystem"));
	}
}

void UServerInstance::LoadMenu()
{

	if (MenuClass)
	{
		Menu = CreateWidget<UMainMenu>(this, MenuClass);

		if (IsValid(Menu))
		{
			Menu->Setup();
			Menu->SetMenuInterface(this);
		}
	}
}

void UServerInstance::InGameLoadMenu()
{
	if (MenuClass)
	{
		UMenuWidget* MainMenu = CreateWidget<UMenuWidget>(this, InGameMenuClass);

		if (IsValid(MainMenu))
		{
			MainMenu->Setup();
			MainMenu->SetMenuInterface(this);
		}
	}
}

void UServerInstance::Host()
{
	if (SessionInterface.IsValid())
	{
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);

		if (nullptr != ExistingSession)
		{
			SessionInterface->DestroySession(SESSION_NAME);

			UE_LOG(LogTemp, Warning, TEXT("Click Host Btn!"));
		}
		else
		{
			CreateSession();
			UE_LOG(LogTemp, Warning, TEXT("Click Host"));
		}
	}
}

void UServerInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't create session"));
		return;
	}

	if (Menu)
	{
		Menu->Teardown();
	}

	if (GWorld)
	{
		UE_LOG(LogTemp, Log, TEXT("ServerTravel to /Game/FirstPerson/Maps/FirstPersonMap?listen"));
		GWorld->ServerTravel("/Game/Maps/Play?listen");
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get World!"));
	}
}

void UServerInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success)
	{
		CreateSession();
	}
}

void UServerInstance::OnFindSessionComplete(bool Success)
{
	if (Success && SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Finished Find Session"));
		for (const FOnlineSessionSearchResult& SearchResult : SessionSearch->SearchResults)
		{

			UE_LOG(LogTemp, Warning, TEXT("Found Session Name : %s"), *SearchResult.GetSessionIdStr());
		}
	}
}

void UServerInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.NumPublicConnections = 2;
		SessionSettings.bShouldAdvertise = true;
		SessionInterface->CreateSession(0, TEXT("My Session Game"), SessionSettings);
	}
}

void UServerInstance::Join(const FString& Address)
{
	if (Menu)
	{
		Menu->Teardown();
	}

	if (!ensure(GEngine != nullptr)) return;

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController)
	{
		PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString::Printf(TEXT("Failed %s"), *Address));
	}
}

void UServerInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController)
	{
		PlayerController->ClientTravel("/Game/Maps/MainMenu?listen", ETravelType::TRAVEL_Absolute);
	}
}
