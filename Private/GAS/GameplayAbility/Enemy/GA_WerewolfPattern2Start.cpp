// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GameplayAbility/Enemy/GA_WerewolfPattern2Start.h"

#include "Character/Enemy/Boss/BossWereWolfCharacter.h"
#include "Controller/AIControllerBase.h"
#include "Controller/GASWorldPlayerController.h"
#include "GameFramework/Character.h"


void UGA_WerewolfPattern2Start::SetTargetInfo()
{
	if (GetCurrentController() && GetCurrentController()->GetFocusActor())
	{
		QTETargetActor = GetCurrentController()->GetFocusActor();
		if (QTETargetActor)
			QTETargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(QTETargetActor);
	}
}

void UGA_WerewolfPattern2Start::ChangePlayerCamera()
{
	if (!QTETargetActor)
		return;

	if (ACharacter* QTETargetCharacter = Cast<ACharacter>(QTETargetActor))
	{
		if (APlayerController* QTETargetPlayerController = Cast<APlayerController>(QTETargetCharacter->GetController()))
		{
			QTETargetPlayerController->SetViewTargetWithBlend(GetAvatarActorFromActorInfo());
		}
	}
}

void UGA_WerewolfPattern2Start::RotateTargetPlayer()
{
	ABossWereWolfCharacter* CurrentQTEBoss = Cast<ABossWereWolfCharacter>(GetAvatarActorFromActorInfo());
	if (CurrentQTEBoss && QTETargetActor)
	{
		CurrentQTEBoss->MultiRotateActor(
			QTETargetActor,
			FRotator(
				0,
				(GetAvatarActorFromActorInfo()->GetActorLocation() - QTETargetActor->GetActorLocation()).Z,
				0
				)
		);
	}
}

void UGA_WerewolfPattern2Start::ShowExtraGaugeUIAndBind()
{
	if (ACharacter* TargetCharacter = Cast<ACharacter>(QTETargetActor))
	{
		AGASWorldPlayerController* TargetPlayerController = Cast<AGASWorldPlayerController>(TargetCharacter->GetController());
		AGASCombatBossNPC* BossWerewolf = Cast<AGASCombatBossNPC>(GetAvatarActorFromActorInfo());

		if (TargetPlayerController && BossWerewolf)
		{
			TargetPlayerController->ClientShowBossExtraGaugeUI();
			TargetPlayerController->BindBossExtraGauge(BossWerewolf);
		}
	}
}
