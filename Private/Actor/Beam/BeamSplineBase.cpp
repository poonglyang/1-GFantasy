// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Beam/BeamSplineBase.h"

#include "Components/SplineComponent.h"


// Sets default values
ABeamSplineBase::ABeamSplineBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BeamSplineComponent = CreateDefaultSubobject<USplineComponent>(FName("BeamSpline"));
	BeamSplineComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABeamSplineBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABeamSplineBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

