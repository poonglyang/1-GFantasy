// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Beam/BeamBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Character/GASCombatNPC.h"
#include "Components/SplineComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Libraries/GASAbilitySystemLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Preferences/PersonaOptions.h"

#define GET_ASC_TO_ACTOR(Actor) UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor)

// Sets default values
ABeamBase::ABeamBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceenRoot"));
	RootComponent = Root;
	
	BeamBody = CreateDefaultSubobject<UParticleSystemComponent>(FName("BeamBody"));
	BeamExplosion = CreateDefaultSubobject<UParticleSystemComponent>(FName("BeamExplosion"));

	BeamBody->SetupAttachment(RootComponent);
	BeamExplosion->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ABeamBase::BeginPlay()
{
	Super::BeginPlay();

	if (BeamBodyParticle && BeamBody)
	{
		BeamBody->SetTemplate(BeamBodyParticle);
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(L"빔 이팩트 설정 완료"));
	}
	else
	{
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(L"빔 이팩트 설정 실패"));
	}

	if (BeamExplosionParticle && BeamExplosion)
		BeamExplosion->SetTemplate(BeamExplosionParticle);
	
}

// Called every frame
void ABeamBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;

	SetStartAndEndPoint();
	
	SetBeamLocation();

	DetectedObject();
}

void ABeamBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(ABeamBase, BeamBodyParticle, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ABeamBase, BeamExplosionParticle, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ABeamBase, BeamOwnerActor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ABeamBase, TargetActor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ABeamBase, Duration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ABeamBase, BeamStartSocketName, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ABeamBase, StartMultiply, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ABeamBase, BeamStartLocation, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ABeamBase, BeamEndLocation, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ABeamBase, BeamRadius, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ABeamBase, BeamHalfHeight, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ABeamBase, DetectObjectType, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ABeamBase, DetectedActorsToIgnore, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ABeamBase, DetectedIgnoreSelf, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ABeamBase, DamageEffectClass, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ABeamBase, bTargetIsActor, COND_None, REPNOTIFY_Always);
}

void ABeamBase::SetBeamLocation()
{
	for (int i = 0 ; i < 11; i++)
	{
		BeamBody->SetBeamSourcePoint(i, BeamStartLocation, 0);
		BeamBody->SetBeamTargetPoint(i, BeamEndLocation, 0);
		BeamExplosion->SetWorldLocation(BeamEndLocation);
	}
}

void ABeamBase::DetectedObject()
{
	if (!DamageEffectClass)
		return;
	
	TArray<FHitResult> OutHits;
	
	if (
		!UKismetSystemLibrary::CapsuleTraceMultiForObjects(
			GetWorld(),
			BeamStartLocation,
			BeamEndLocation,
			BeamRadius,
			BeamHalfHeight,
			DetectObjectType,
			false,
			DetectedActorsToIgnore,
			EDrawDebugTrace::None,
			OutHits,
			DetectedIgnoreSelf
		)
	)
	return;

	for (FHitResult Hit : OutHits)
	{
		if (DetectedActors.Find(Hit.GetActor()))
			continue;
		
		if (BeamOwnerActor && GET_ASC_TO_ACTOR(BeamOwnerActor)
			&& Hit.GetActor() && GET_ASC_TO_ACTOR(Hit.GetActor()))
		{
			UGASAbilitySystemLibrary::ApplyGASEffectToTargetToASC(
				GET_ASC_TO_ACTOR(BeamOwnerActor),
				GET_ASC_TO_ACTOR(Hit.GetActor()),
				DamageEffectClass
			);

			DetectedActors.Add(Hit.GetActor());

			if (GetWorld())
			{
				FTimerHandle PopFrontTimer;
				GetWorld()->GetTimerManager().SetTimer(
					PopFrontTimer,
					this,
					&ABeamBase::PopFrontActor,
					DamageTick,
					false);
			}
		}
	}

	
}

void ABeamBase::SetStartAndEndPoint()
{
	if (!BeamOwnerActor || !BeamOwnerActor->GetMesh())
		return;

	BeamStartLocation = BeamOwnerActor->GetMesh()
		->GetSocketLocation(BeamStartSocketName) + BeamOwnerActor->GetActorForwardVector() * StartMultiply;

	if (TargetActor && bTargetIsActor)
	{
		BeamEndLocation = TargetActor->GetActorLocation();
	}
	else if (BeamSplineActor && BeamSplineActor->BeamSplineComponent)
	{
		BeamEndLocation = BeamSplineActor->BeamSplineComponent
			->GetLocationAtDistanceAlongSpline(
				BeamSplineActor->BeamSplineComponent->GetSplineLength() * FMath::Clamp(
					ElapsedTime / Duration, 0.0f, 1.0f
				),
				ESplineCoordinateSpace::World
			);
	}
}



void ABeamBase::ChangeTargetActor(AActor* NewTargetActor)
{
	TargetActor = NewTargetActor;
}

void ABeamBase::BeamEnd()
{
	GetWorldTimerManager().ClearAllTimersForObject(this);
	Destroy();
}

void ABeamBase::PopFrontActor()
{
	
}