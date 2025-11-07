// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GameplayAbility/GA_EndDelegateBase.h"
#include "GA_WerewolfPattern2Loop.generated.h"

/**
 * 
 */
class AAIController;

UCLASS()
class GFANTASY_API UGA_WerewolfPattern2Loop : public UGA_EndDelegateBase
{
	GENERATED_BODY()
	
protected:
	AAIController* GetBossAIController() const;
	
	UFUNCTION(BlueprintCallable, Category = "WerewolfPattern2Loop")
	void SetTargetInfo();

	UFUNCTION(BlueprintCallable, Category = "WerewolfPattern2Loop")
	void ExtraGaugeFull();
	
	UFUNCTION(BlueprintCallable, Category = "WerewolfPattern2Loop")
	bool PlayerHit(FGameplayAttribute HealthAttribute);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WerewolfPattern2Loop")
	AActor* QTETargetActor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WerewolfPattern2Loop")
	UAbilitySystemComponent* QTETargetASC;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WerewolfPattern2Loop")
	TSubclassOf<UCameraShakeBase> TargetHitCameraShake;
	
};
