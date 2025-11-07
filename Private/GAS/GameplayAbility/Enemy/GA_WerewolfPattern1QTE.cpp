// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GameplayAbility/Enemy/GA_WerewolfPattern1QTE.h"

#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Character/Enemy/Boss/BossWereWolfCharacter.h"
#include "Controller/AIControllerBase.h"
#include "GameFramework/Character.h"

void UGA_WerewolfPattern1QTE::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// FGameplayTag EventTag
	// 	= FGameplayTag::RequestGameplayTag(TEXT("Combat.Pattern1.End.TargetAlive"));
	//
	// WaitTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
	// 		this,
	// 		EventTag,
	// 		QTETargetActor,
	// 		false,           
	// 		false            
	// 	);
	//
	// if (WaitTask)
	// {
	// 	WaitTask->EventReceived.AddDynamic(
	// 		this,
	// 		&UGA_WerewolfPattern1QTE::PlayerAliveToPattern
	// 		);
	// 	WaitTask->ReadyForActivation();
	// }
}

void UGA_WerewolfPattern1QTE::SetTargetInfo()
{
	if (GetCurrentController() && GetCurrentController()->GetFocusActor())
	{
		QTETargetActor = GetCurrentController()->GetFocusActor();
		if (QTETargetActor)
			QTETargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(QTETargetActor);
	}
}

void UGA_WerewolfPattern1QTE::TargetActorChangeTransform()
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

		CurrentQTEBoss->MultiSetLocationActor(
			QTETargetActor,
			(
				GetAvatarActorFromActorInfo()->GetActorForwardVector() * FVector(220,220,220)
				+ GetAvatarActorFromActorInfo()->GetActorLocation()
				)
		);
	}
}

void UGA_WerewolfPattern1QTE::ChangePlayerCamera()
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

void UGA_WerewolfPattern1QTE::PlayerAlive()
{
	if (GetCurrentController())
	{
		GetCurrentController()->ClearFocus(EAIFocusPriority::Default);
	}

	bIsPlayerAlive = true;
}

void UGA_WerewolfPattern1QTE::PlayerAliveToPattern(FGameplayEventData Payload)
{
	
}
