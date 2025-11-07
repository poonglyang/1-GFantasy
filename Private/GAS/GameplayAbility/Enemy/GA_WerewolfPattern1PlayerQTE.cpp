// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GameplayAbility/Enemy/GA_WerewolfPattern1PlayerQTE.h"

#include "Controller/GASWorldPlayerController.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"


void UGA_WerewolfPattern1PlayerQTE::SetQTETargetPlayer()
{
	if (!GetAvatarActorFromActorInfo())
		return;

	if (Cast<ACharacter>(GetAvatarActorFromActorInfo()))
		TargetPlayer = Cast<AGASWorldPlayerController>(Cast<ACharacter>(GetAvatarActorFromActorInfo())->GetController());
}

void UGA_WerewolfPattern1PlayerQTE::QTEProgressBarStart()
{
	if (!TargetPlayer)
		return;

	TargetPlayer->ClientShowWerewolfPattern1Progressbar();

	GetWorld()->GetTimerManager().SetTimer(
		ProgressBarTimerHandle,
		this,
		&UGA_WerewolfPattern1PlayerQTE::QTEProgressBarLoop,
		LoopTime,
		true
	);
}

void UGA_WerewolfPattern1PlayerQTE::QTEProgressBarLoop()
{
	if (!TargetPlayer)
		return;
	
	ElapsedTime += LoopTime;
	
	TargetPlayer->ClientSetWerewolfPattern1ProgressbarPercent(UKismetMathLibrary::Lerp(1,0,ElapsedTime / QTETime));
}

void UGA_WerewolfPattern1PlayerQTE::PlayerClearQTE()
{
	if (ProgressBarTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ProgressBarTimerHandle);
	}

	if (TargetPlayer)
		TargetPlayer->ClientHideWerewolfPattern1Progressbar();

	bIsPlayerHit = true;
}

void UGA_WerewolfPattern1PlayerQTE::RestorePlayerCamera()
{
	if (TargetPlayer)
		TargetPlayer->SetViewTargetWithBlend(GetAvatarActorFromActorInfo());

	bIsCameraRestore = true;
}

void UGA_WerewolfPattern1PlayerQTE::InitAbility()
{
	if (!bIsCameraRestore)
	{
		RestorePlayerCamera();
		bIsCameraRestore = false;
	}

	ElapsedTime = 0;

	if (ProgressBarTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ProgressBarTimerHandle);
	}

	TargetPlayer->ClientHideWerewolfPattern1Progressbar();
}
