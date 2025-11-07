// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GameplayAbility/Enemy/GA_SuccubusNormalAttack2.h"

#include "AIController.h"
#include "Actor/Beam/BeamBase.h"
#include "Actor/Beam/BeamSplineBase.h"
#include "Character/GASCombatNPC.h"
#include "Components/SplineComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


AActor* UGA_SuccubusNormalAttack2::GetCurrentFocusActor() const
{
	AGASCombatNPC* SpawnActor = Cast<AGASCombatNPC>(GetAvatarActorFromActorInfo());
	if (!SpawnActor)
		return nullptr;
	
	AAIController* CurrentBossController = Cast<AAIController>(SpawnActor->GetController());

	if (!CurrentBossController && !CurrentBossController->GetFocusActor())
		return nullptr;

	return CurrentBossController->GetFocusActor();
}

FTransform UGA_SuccubusNormalAttack2::GetSpawnPoint() const
{
	AActor* CurrentBoss = GetAvatarActorFromActorInfo();

	
	if (!CurrentBoss && GetCurrentFocusActor())
		return FTransform();
	else
	{
		//UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(L"%lf", FVector::Distance(GetCurrentFocusActor()->GetActorLocation(), CurrentBoss->GetActorLocation())));
		if (FVector::Distance(GetCurrentFocusActor()->GetActorLocation(), CurrentBoss->GetActorLocation()) < 800)
		{
			return FTransform(
				CurrentBoss->GetActorRotation() + FRotator(0, 90, 0),
				CurrentBoss->GetActorLocation() + CurrentBoss->GetActorForwardVector() * 800 - PlayerHeight,
				FVector(1,1,1)
			);
		}
		else
		{
			return FTransform(
				CurrentBoss->GetActorRotation() + FRotator(0, 90, 0),
				GetCurrentFocusActor()->GetActorLocation() - PlayerHeight,
				FVector(1,1,1)
			);
		}
	}
}

void UGA_SuccubusNormalAttack2::SetBeamSpline(AActor* NewBeamSpline)
{
	FTransform SplineTransform = GetSpawnPoint();
	NewBeamSpline->SetActorTransform(SplineTransform);
	
	CurrentBeamSpline = Cast<ABeamSplineBase>(NewBeamSpline);	
}

void UGA_SuccubusNormalAttack2::SetBeam(AActor* NewBeam)
{
	CurrentBeam = Cast<ABeamBase>(NewBeam);
}

void UGA_SuccubusNormalAttack2::LookBeamEndStart()
{
	GetWorld()->GetTimerManager().SetTimer(
		LookBeamEndTimer,
		this,
		&UGA_SuccubusNormalAttack2::LookBeamEndLoop,
		0.03f,
		true
	);
}

void UGA_SuccubusNormalAttack2::LookBeamEndLoop()
{
	AActor* CurrentBoss = GetAvatarActorFromActorInfo();
	
	if (!CurrentBeam || !LookBeamEndTimer.IsValid() || !CurrentBoss)
	{
		GetWorld()->GetTimerManager().ClearTimer(LookBeamEndTimer);
		return;
	}

	CurrentBoss->SetActorRotation(
		UKismetMathLibrary::RInterpTo(
			CurrentBoss->GetActorRotation(),
			UKismetMathLibrary::FindLookAtRotation(
				CurrentBoss->GetActorLocation(),
				CurrentBeam->BeamEndLocation
			),
			0.03f,
			1.0f
		)
	);
}

void UGA_SuccubusNormalAttack2::RotateSplineStart()
{
	GetWorld()->GetTimerManager().SetTimer(
		RotateSplineTimer,
		this,
		&UGA_SuccubusNormalAttack2::RotateSplineLoop,
		0.03f,
		true
	);
}

void UGA_SuccubusNormalAttack2::RotateSplineLoop()
{
	AActor* CurrentBoss = GetAvatarActorFromActorInfo();
	
	if (!CurrentBeamSpline || !CurrentBeamSpline->BeamSplineComponent || !CurrentBoss)
	{
		GetWorld()->GetTimerManager().ClearTimer(RotateSplineTimer);
		return;
	}

	CurrentBoss->SetActorRotation(
		UKismetMathLibrary::RInterpTo(
			CurrentBoss->GetActorRotation(),
			UKismetMathLibrary::FindLookAtRotation(CurrentBoss->GetActorLocation(), CurrentBeamSpline->BeamSplineComponent->GetLocationAtDistanceAlongSpline(0, ESplineCoordinateSpace::World)),
			0.03f,
			2.0f
		)
	);
}

FSpawnData UGA_SuccubusNormalAttack2::CheckCanSpawnBeam()
{
	AGASCombatNPC* SpawnActor = Cast<AGASCombatNPC>(GetAvatarActorFromActorInfo());
	if (!SpawnActor)
		return FSpawnData(false, nullptr, nullptr, FVector::ZeroVector, FRotator::ZeroRotator);
	
	AAIController* CurrentBossController = Cast<AAIController>(SpawnActor->GetController());

	if (!CurrentBossController || !CurrentBeamSpline)
		return FSpawnData(false, SpawnActor, nullptr, FVector::ZeroVector, FRotator::ZeroRotator);;

	AActor* Target = CurrentBossController->GetFocusActor();

	CurrentBossController->ClearFocus(EAIFocusPriority::Gameplay);
	
	return FSpawnData(true, SpawnActor, Target, SpawnActor->GetActorLocation(), SpawnActor->GetActorRotation());
}


