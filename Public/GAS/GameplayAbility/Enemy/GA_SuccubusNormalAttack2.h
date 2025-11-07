// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/GameplayAbility/GA_EndDelegateBase.h"
#include "GA_SuccubusNormalAttack2.generated.h"

class ABeamBase;
class ABeamSplineBase;
class AGASCombatNPC;
/**
 * 
 */


USTRUCT(BlueprintType)
struct FSpawnData
{
	GENERATED_BODY()
	FSpawnData()
	{
		bCanSpawnBeam = false;
		SpawnActor = nullptr;
		Target = nullptr;
		SpawnLocation = FVector::ZeroVector;
		SpawnRotator = FRotator::ZeroRotator;
	}
	
	FSpawnData(bool bCanSpawnBeam, AGASCombatNPC* SpawnActor, AActor* Target, FVector SpawnLocation, FRotator SpawnRotator)
		: bCanSpawnBeam(bCanSpawnBeam), SpawnActor(SpawnActor), Target(Target), SpawnLocation(SpawnLocation), SpawnRotator(SpawnRotator) {};
		
	UPROPERTY(BlueprintReadWrite)
	bool bCanSpawnBeam;

	UPROPERTY(BlueprintReadWrite)
	FVector SpawnLocation;

	UPROPERTY(BlueprintReadWrite)
	FRotator SpawnRotator;
	
	UPROPERTY(BlueprintReadWrite)
	AGASCombatNPC* SpawnActor;

	UPROPERTY(BlueprintReadWrite)
	AActor* Target;
};



UCLASS()
class GFANTASY_API UGA_SuccubusNormalAttack2 : public UGA_EndDelegateBase
{
	GENERATED_BODY()

protected:
	AActor* GetCurrentFocusActor() const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SuccubusNormalAttack2")
	FTransform GetSpawnPoint() const;

	UFUNCTION(BlueprintCallable, Category = "SuccubusNormalAttack2")
	void SetBeamSpline(AActor* NewBeamSpline);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SuccubusNormalAttack2")
	FSpawnData CheckCanSpawnBeam();
	
	UFUNCTION(BlueprintCallable, Category = "SuccubusNormalAttack2")
	void SetBeam(AActor* NewBeam);
	
	UFUNCTION(BlueprintCallable, Category = "SuccubusNormalAttack2")
	void LookBeamEndStart();

	UFUNCTION(BlueprintCallable, Category = "SuccubusNormalAttack2")
	void LookBeamEndLoop();

	UFUNCTION(BlueprintCallable, Category = "SuccubusNormalAttack2")
	void RotateSplineStart();

	UFUNCTION(BlueprintCallable, Category = "SuccubusNormalAttack2")
	void RotateSplineLoop();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SuccubusNormalAttack2")
	ABeamBase* CurrentBeam;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SuccubusNormalAttack2")
	ABeamSplineBase* CurrentBeamSpline;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SuccubusNormalAttack2")
	FTimerHandle LookBeamEndTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SuccubusNormalAttack2")
	FTimerHandle RotateSplineTimer;

	UPROPERTY()
	FVector PlayerHeight = FVector(0.0f, 0.0f, 90.f);
};
