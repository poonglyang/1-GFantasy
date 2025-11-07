// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GameplayAbility/Enemy/GA_SuccubusNormalAttack1.h"

#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"


FVector UGA_SuccubusNormalAttack1::GetShotVelocity()
{
	APawn* AsPawn = Cast<APawn>(GetAvatarActorFromActorInfo());
	if (!AsPawn)
		return FVector::Zero();
	
	AAIController* CurrentBossController = Cast<AAIController>(AsPawn->GetController());

	if (CurrentBossController && CurrentBossController->GetFocusActor())
	{
		return UKismetMathLibrary::Normal
		(
			CurrentBossController->GetFocusActor()->GetActorLocation()
			+ FVector(0.0f, 0.0f, -100.0f)
			- GetAvatarActorFromActorInfo()->GetActorLocation()
		);
	}
	else
	{
		return FVector::Zero();
	}
}
