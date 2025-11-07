// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GameplayAbility/GA_EndDelegateBase.h"
#include "GA_WerewolfPattern1QTE.generated.h"

/**
 * 
 */
class UAbilityTask_WaitGameplayEvent;

UCLASS()
class GFANTASY_API UGA_WerewolfPattern1QTE : public UGA_EndDelegateBase
{
	GENERATED_BODY()
	
protected:
	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION(BlueprintCallable, Category = "WerewolfPattern1QTE")
	void SetTargetInfo();

	UFUNCTION(BlueprintCallable, Category = "WerewolfPattern1QTE")
	void TargetActorChangeTransform();

	UFUNCTION(BlueprintCallable, Category = "WerewolfPattern1QTE")
	void ChangePlayerCamera();

	UFUNCTION(BlueprintCallable, Category = "WerewolfPattern1QTE")
	void PlayerAlive();

	UFUNCTION(BlueprintCallable, Category = "WerewolfPattern1QTE")
	void PlayerAliveToPattern(FGameplayEventData Payload);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WerewolfPattern1QTE")
	AActor* QTETargetActor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WerewolfPattern1QTE")
	UAbilitySystemComponent* QTETargetASC;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WerewolfPattern1QTE")
	bool bIsPlayerAlive = false;

	UPROPERTY()
	UAbilityTask_WaitGameplayEvent* WaitTask;
};
