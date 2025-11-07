// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GameplayAbility/GA_EndDelegateBase.h"
#include "GA_WerewolfPattern2Start.generated.h"

/**
 * 
 */
UCLASS()
class GFANTASY_API UGA_WerewolfPattern2Start : public UGA_EndDelegateBase
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Category = "WerewolfPattern2")
	void SetTargetInfo();
	
	UFUNCTION(BlueprintCallable, Category = "WerewolfPattern2")
	void ChangePlayerCamera();

	UFUNCTION(BlueprintCallable, Category = "WerewolfPattern2")
	void RotateTargetPlayer();
	
	UFUNCTION(BlueprintCallable, Category = "WerewolfPattern2")
	void ShowExtraGaugeUIAndBind();
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WerewolfPattern1QTE")
	AActor* QTETargetActor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WerewolfPattern1QTE")
	UAbilitySystemComponent* QTETargetASC;
	
};
