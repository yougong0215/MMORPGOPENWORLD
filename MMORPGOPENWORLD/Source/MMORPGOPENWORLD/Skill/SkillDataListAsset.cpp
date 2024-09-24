// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillDataListAsset.h"
#include "CollisionObject.h"
#include "EffectObject.h"

void USkillDataListAsset::SetFire(TObjectPtr<AActor> OwnerCS, UWorld* _world)
{

    for (int i = 0; i < SkillList.Num(); i++)
    {

        if (EffectObjectBPClass)
        {
            //if(GetWorld())
            AEffectObject* obj = _world->SpawnActor<AEffectObject>(EffectObjectBPClass);


            obj->Begin(OwnerCS, SkillList[i], _world);
        }

    }
}
