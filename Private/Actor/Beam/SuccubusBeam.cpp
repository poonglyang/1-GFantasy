// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Beam/SuccubusBeam.h"

#include "Character/Enemy/Boss/BossSuccubusCharacter.h"


void ASuccubusBeam::SetStartAndEndPoint()
{
	Super::SetStartAndEndPoint();

	if (ABossSuccubusCharacter* CurrentOwnerActor = Cast<ABossSuccubusCharacter>(BeamOwnerActor))
	{
		BeamStartLocation = CurrentOwnerActor->GetArmSocketLocation() + CurrentOwnerActor->GetActorForwardVector() * StartMultiply;
	}
	
	 
}
