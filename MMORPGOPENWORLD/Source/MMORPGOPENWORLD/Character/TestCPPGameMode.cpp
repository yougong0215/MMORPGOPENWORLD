// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestCPPGameMode.h"
#include "TestCPPCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"

// 생성자
ATestCPPGameMode::ATestCPPGameMode()
{
    PrimaryActorTick.bCanEverTick = true; // Tick을 활성화

    // 초기 기본 캐릭터 클래스를 설정
    UpdateDefaultPawnClass();
}

// Tick 함수
void ATestCPPGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 매 프레임마다 기본 캐릭터 클래스를 업데이트
    UpdateDefaultPawnClass();
}

// 기본 캐릭터 클래스를 업데이트하는 함수
void ATestCPPGameMode::UpdateDefaultPawnClass()
{
    // 캐릭터 클래스를 배열로 관리
    TArray<FString> CharacterPaths = {
        TEXT("/Game/Characters/BasicCharacter"),
        TEXT("/Game/Characters/BasicCharacter2"),
        TEXT("/Game/Characters/BasicCharacter3"),
        TEXT("/Game/Characters/BasicCharacter4"),
        TEXT("/Game/Characters/BasicCharacter5"),
        TEXT("/Game/Characters/BasicCharacter6"),
        TEXT("/Game/Characters/BasicCharacter7"),
        TEXT("/Game/Characters/BasicCharacter8"),
        TEXT("/Game/Characters/BasicCharacter9"),
        TEXT("/Game/Characters/BasicCharacter10")
    };

    // 랜덤으로 하나 선택
    int32 RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, CharacterPaths.Num() - 1);

    // 선택한 경로로 FClassFinder 사용
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(*CharacterPaths[RandomIndex]);

    if (PlayerPawnBPClass.Succeeded())
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}