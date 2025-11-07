// Fill out your copyright notice in the Description page of Project Settings.
#include "Character/Animation/ANS_UpdatePlayerDirection.h"
#include "Character/GASPlayerCharacter.h"


void UANS_UpdatePlayerDirection::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{

}

void UANS_UpdatePlayerDirection::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (AGASPlayerCharacter* Char = Cast<AGASPlayerCharacter>(MeshComp->GetOwner()))
	{
		FVector Dir = Char->CachedInputDirection;
		if (Char->TargetingState == ETargetingState::LockOn && Char->CurrentTarget)
		{
			FVector ToTarget = (Char->CurrentTarget->GetActorLocation() - Char->GetActorLocation()).GetSafeNormal2D();
			FRotator Rot = ToTarget.Rotation(); 
			Char->GetRootComponent()->SetWorldRotation(Rot);
			return;
		}

		if (!Dir.IsNearlyZero())
		{
			// 한 번만 즉시 회전
			Char->GetRootComponent()->SetWorldRotation(Dir.Rotation());
				//SetActorRotation(Dir.Rotation());
		}
	}
}
