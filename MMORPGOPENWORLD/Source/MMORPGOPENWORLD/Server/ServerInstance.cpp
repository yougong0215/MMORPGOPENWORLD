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

const static FName SESSION_NAME = TEXT("MySessionGame");
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

			/*SessionSearch = MakeShareable(new FOnlineSessionSearch());
			if (SessionSearch)
			{
				SessionSearch->bIsLanQuery = true;
				SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
			}*/
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
		// 세션 검색을 시작합니다.
		SessionSearch = MakeShareable(new FOnlineSessionSearch());
		if (SessionSearch)
		{
			SessionSearch->bIsLanQuery = true;
			UE_LOG(LogTemp, Warning, TEXT("Starting to find sessions"));

			// 세션을 검색하고 완료 시 콜백을 처리합니다.
			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			if (SessionSearch)
			{
				SessionSearch->bIsLanQuery = true;
				SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
			}
			//SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UServerInstance::OnFindSessionComplete);
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
		UE_LOG(LogTemp, Log, TEXT("ServerTravel to /Game/FirstPerson/Maps/Play?listen"));
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

	if (Success && SessionSearch.IsValid() && SessionSearch->SearchResults.Num() > 0)
	{
		// 세션이 존재하는 경우
		UE_LOG(LogTemp, Warning, TEXT("Found sessions, joining the first available session"));

		// 현재 세션에 참가 중인지 확인
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession != nullptr)
		{
			// 이미 세션에 참가 중인 경우 세션을 종료
			UE_LOG(LogTemp, Warning, TEXT("Already in a session, leaving current session to join a new one."));
			SessionInterface->DestroySession(SESSION_NAME);
		}

		// 첫 번째 세션에 참가
		FString Address = TEXT("172.31.2.235"); // 올바른 IP와 포트
		
		Join(Address);
	}
	else
	{
		// 세션이 없으므로 새 세션 생성
		UE_LOG(LogTemp, Warning, TEXT("No sessions found, creating a new session"));
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);

		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}
	}
}

void UServerInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.NumPublicConnections = 50;
		SessionSettings.bAllowJoinInProgress = true;
		SessionSettings.bShouldAdvertise = true;

		FString SessionName = FString::Printf(TEXT("MySessionGame_%lld"), FDateTime::Now().GetTicks());
		SessionInterface->CreateSession(0, FName(*SessionName), SessionSettings);
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
