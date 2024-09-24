// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillDataListAsset.h"
#include "CollisionObject.h"
#include "EffectObject.h"
#include "Net/UnrealNetwork.h"

void USkillDataListAsset::SetFire(TObjectPtr<AActor> OwnerCS, UWorld* _world)
{
    for (int i = 0; i < SkillList.Num(); i++)
    {

        if (EffectObjectBPClass)
        {
            AEffectObject* obj = _world->SpawnActor<AEffectObject>(EffectObjectBPClass);

            if (obj)
            {
                obj->Begin(OwnerCS, SkillList[i], _world);
                obj->SetReplicates(true); // 복제 가능하도록 설정
            }
        }

    }
}