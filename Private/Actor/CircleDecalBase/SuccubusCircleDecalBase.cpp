// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/CircleDecalBase/SuccubusCircleDecalBase.h"

#include "Net/UnrealNetwork.h"


void ASuccubusCircleDecalBase::SpawnBallInArea(int Count)
{
	
}

void ASuccubusCircleDecalBase::SpreadPatternBallInArea(int Count)
{
	
}

void ASuccubusCircleDecalBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(ASuccubusCircleDecalBase, PatternBallArr, COND_None, REPNOTIFY_Always);
}
