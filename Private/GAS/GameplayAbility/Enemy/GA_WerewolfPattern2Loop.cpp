// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GameplayAbility/Enemy/GA_WerewolfPattern2Loop.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Controller/AIControllerBase.h"
#include "GAS/GamePlayTag.h"
#include "GAS/AttributeSet/GASCharacterAS.h"


AAIController* UGA_WerewolfPattern2Loop::GetBossAIController() const
{
	APawn* AsPawn = Cast<APawn>(GetAvatarActorFromActorInfo());
	if (!AsPawn)
		return nullptr;
	
	return Cast<AAIController>(AsPawn->GetController());
}

void UGA_WerewolfPattern2Loop::SetTargetInfo()
{
	if (GetCurrentController() && GetCurrentController()->GetFocusActor())
	{
		QTETargetActor = GetCurrentController()->GetFocusActor();
		if (QTETargetActor)
			QTETargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(QTETargetActor);
	}
}

void UGA_WerewolfPattern2Loop::ExtraGaugeFull()
{
	AAIController* CurrentBossAIController = GetBossAIController();

	if (!CurrentBossAIController && !CurrentBossAIController->GetBlackboardComponent())
		return;
	
	CurrentBossAIController->GetBlackboardComponent()->SetValueAsBool(FName("bCanGroundPattern"), false);
	CurrentBossAIController->GetBlackboardComponent()->SetValueAsBool(FName("bGroundPatternPlayerDie"), false);
	
	// 플레이어에게 Loop Ability 종료 이벤트 실행
	FGameplayEventData Payload;
	QTETargetASC->HandleGameplayEvent(FGameplayTags::Get().Combat_Pattern1_Loop, &Payload);

	
	
}

bool UGA_WerewolfPattern2Loop::PlayerHit(FGameplayAttribute HealthAttribute)
{
	APawn* TargetPawn = Cast<APawn>(QTETargetActor);
	if (!TargetPawn)
		return false;

	
	if (APlayerController* CurrentTargetController = Cast<APlayerController>(TargetPawn->GetController()))
	{
		// 카메라 흔들기
		CurrentTargetController->ClientStartCameraShake(TargetHitCameraShake);
	}

	bool Found;
	float TargetHealth = QTETargetASC->GetGameplayAttributeValue(HealthAttribute, Found);

	if (!Found || TargetHealth > 0)
		return false;

	AAIController* CurrentBossAIController = GetBossAIController();

	CurrentBossAIController->GetBlackboardComponent()->SetValueAsBool(FName("bCanGroundPattern"), false);
	CurrentBossAIController->GetBlackboardComponent()->SetValueAsBool(FName("bGroundPatternPlayerDie"), true);

	// 플레이어에게 Loop Ability 종료 이벤트 실행
	FGameplayEventData Payload;
	QTETargetASC->HandleGameplayEvent(FGameplayTags::Get().Combat_Pattern1_Loop, &Payload);

	return true;
	
}
