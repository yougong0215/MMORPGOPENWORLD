// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestCPPGameMode.h"
#include "TestCPPCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"

ATestCPPGameMode::ATestCPPGameMode()
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