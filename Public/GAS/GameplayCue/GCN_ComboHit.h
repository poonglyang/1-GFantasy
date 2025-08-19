// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GCN_ComboHit.generated.h"

class UNiagaraSystem;

UCLASS(meta=(DisplayName = "Combo Hit Effect"))
class GFANTASY_API UGCN_ComboHit : public UGameplayCueNotify_Static
{
	GENERATED_BODY()

public:

	//��ƼŬ�̳� ����Ʈ ������ �����Ϳ��� �Ҵ�
	UPROPERTY(EditDefaultsOnly, Category = "Cue")
	UNiagaraSystem* HitEffect;

	//virtual bool HandleGameplayCue(
	//	AActor* MyTarget,
	//	EGameplayCueEvent::Type EventType,
	//	const FGameplayCueParameters& Params
	//) const override;
	
	
	
	
};
