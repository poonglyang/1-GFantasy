// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/ANS_RotateCurrentTarget.h"

#include "Character/GASPlayerCharacter.h"


void UANS_RotateCurrentTarget::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                           float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (AGASPlayerCharacter* Char = Cast<AGASPlayerCharacter>(MeshComp->GetOwner()))
	{
		FVector Dir = Char->CachedInputDirection;
		if (Char->CurrentTarget)
		{
			FVector ToTarget = (Char->CurrentTarget->GetActorLocation() - Char->GetActorLocation()).GetSafeNormal2D();
			FRotator Rot = ToTarget.Rotation(); 
			Char->GetRootComponent()->SetWorldRotation(Rot);
			
			// if (Char->GetController()) 
			// {
			// 	Char->GetController()->SetControlRotation(Rot);
			// }
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
