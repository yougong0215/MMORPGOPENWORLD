// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "../Skill/SkillDataListAsset.h"
#include "TestCPPCharacter.generated.h"

class UABCharacterStatComponent;

UCLASS(config=Game)
class ATestCPPCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FireAction3;

public:
	ATestCPPCharacter();
	

protected:

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

public:
	void Fire();
	void Fire1();
	void Fire2();
	void Fire3();
	void Fire4();


protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void BeginPlay();

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire1(); // 서버에서 Fire 호출

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire2(); // 서버에서 Fire 호출

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire3(); // 서버에서 Fire 호출

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire4(); // 서버에서 Fire 호출

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skills", Replicated)
	TArray<USkillDataListAsset*> SkillList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skills", Replicated)
	TObjectPtr<class USkillDataListAsset> Skill;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skills", Replicated)
	TObjectPtr<class USkillDataListAsset> Skill1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skills", Replicated)
	TObjectPtr<class USkillDataListAsset> Skill2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skills", Replicated)
	TObjectPtr<class USkillDataListAsset> Skill3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skills", Replicated)
	TObjectPtr<class USkillDataListAsset> Skill4;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	TObjectPtr<UABCharacterStatComponent> CharacterStat;
	
public:
	void AssignRandomSkill();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

