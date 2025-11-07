// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GameplayAbility/GA_Base.h"
#include "GA_WerewolfPattern1PlayerQTE.generated.h"

class AGASWorldPlayerController;
/**
 * 
 */
UCLASS()
class GFANTASY_API UGA_WerewolfPattern1PlayerQTE : public UGA_Base
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "WerewolfPattern1QTE")
	void SetQTETargetPlayer();
	
	UFUNCTION(BlueprintCallable, Category = "WerewolfPattern1QTE")
	void QTEProgressBarStart();

	UFUNCTION(BlueprintCallable, Category = "WerewolfPattern1QTE")
	void QTEProgressBarLoop();
	
	UFUNCTION(BlueprintCallable, Category = "WerewolfPattern1QTE")
	void PlayerClearQTE();

	UFUNCTION(BlueprintCallable, Category = "WerewolfPattern1QTE")
	void RestorePlayerCamera();

	UFUNCTION(BlueprintCallable, Category = "WerewolfPattern1QTE")
	void InitAbility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WerewolfPattern1QTE")
	FTimerHandle ProgressBarTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WerewolfPattern1QTE")
	float ElapsedTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WerewolfPattern1QTE")
	float LoopTime = 0.03f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WerewolfPattern1QTE")
	float QTETime = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WerewolfPattern1QTE")
	bool bIsPlayerHit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WerewolfPattern1QTE")
	AGASWorldPlayerController* TargetPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WerewolfPattern1QTE")
	bool bIsCameraRestore = false;
	
};
