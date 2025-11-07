// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GameplayAbility/GA_EndDelegateBase.h"
#include "GA_SuccubusNormalAttack1.generated.h"

/**
 * 
 */
UCLASS()
class GFANTASY_API UGA_SuccubusNormalAttack1 : public UGA_EndDelegateBase
{
	GENERATED_BODY()

	protected:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SuccubusNormalAttack1")
	FVector GetShotVelocity();
	
	
};
