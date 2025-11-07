// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/CircleDecalBase/CircleDecalBase.h"
#include "SuccubusCircleDecalBase.generated.h"

class ASuccubusPatternBall;
/**
 * 
 */
UCLASS()
class GFANTASY_API ASuccubusCircleDecalBase : public ACircleDecalBase
{
	GENERATED_BODY()
	
	
public:
	void SpawnBallInArea(int Count);

	void SpreadPatternBallInArea(int Count);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override ;
	
protected:
	UPROPERTY(VisibleAnywhere, Replicated, Category = "CircleDecalBase")
	TArray<ASuccubusPatternBall*> PatternBallArr;
};
