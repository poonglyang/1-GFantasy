// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/CircleDecalBase/CircleDecalBase.h"

#include "Components/DecalComponent.h"
#include "Components/TimelineComponent.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ACircleDecalBase::ACircleDecalBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Arc = CreateDefaultSubobject<UDecalComponent>(TEXT("Arc"));
	Arc->SetupAttachment(RootComponent);
	
	Area = CreateDefaultSubobject<UDecalComponent>(TEXT("Area"));
	Area->SetupAttachment(RootComponent);

	DecalAreaTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("ChestOpenTimeline"));
}

void ACircleDecalBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(ACircleDecalBase, AreaDynamicMaterialInstance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ACircleDecalBase, ArcDynamicMaterialInstance, COND_None, REPNOTIFY_Always);
}

// Called when the game starts or when spawned
void ACircleDecalBase::BeginPlay()
{
	Super::BeginPlay();
	CreateDynamicMaterial();
}

// Called every frame
void ACircleDecalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACircleDecalBase::CreateDynamicMaterial()
{
	if (!ArcDynamicMaterialInstance)
		ArcDynamicMaterialInstance = Arc->CreateDynamicMaterialInstance();

	if (!AreaDynamicMaterialInstance)
		AreaDynamicMaterialInstance = Area->CreateDynamicMaterialInstance();
}

void ACircleDecalBase::ChangeAreaDecalSize(float NewSize)
{
	if (AreaDynamicMaterialInstance)
		AreaDynamicMaterialInstance->SetScalarParameterValue(FName("AreaValue"), NewSize);
}

void ACircleDecalBase::ChangeCircleDecal_Implementation(UCurveFloat* Curve)
{
	FOnTimelineFloat ProgressFunction;
	ProgressFunction.BindUFunction(this, FName("ChangeAreaDecalSize"));
	
	DecalAreaTimeline->AddInterpFloat(Curve, ProgressFunction);
	DecalAreaTimeline->SetLooping(false); // 루프 여부
	DecalAreaTimeline->SetPlayRate(1.0f); // 속도

	DecalAreaTimeline->PlayFromStart(); // 재생
}

void ACircleDecalBase::InitCircleDecal_Implementation()
{
	if (ArcDynamicMaterialInstance)
		ArcDynamicMaterialInstance->SetScalarParameterValue(FName("Circum1Area0"), 1);

	if (AreaDynamicMaterialInstance)
		AreaDynamicMaterialInstance->SetScalarParameterValue(FName("Circum1Area0"), 0);
}

void ACircleDecalBase::SetDecalColor_Implementation(FLinearColor Color)
{
	if (ArcDynamicMaterialInstance && AreaDynamicMaterialInstance)
	{
		ArcDynamicMaterialInstance->SetVectorParameterValue(FName("DecalColor"), Color);
		AreaDynamicMaterialInstance->SetVectorParameterValue(FName("DecalColor"), Color);
	}
}

void ACircleDecalBase::SetDecalRadius_Implementation(float NewRadius)
{
	if (ArcDynamicMaterialInstance && AreaDynamicMaterialInstance)
	{
		Radius = NewRadius;
		ArcDynamicMaterialInstance->SetScalarParameterValue(FName("RadianValue"), NewRadius);
		AreaDynamicMaterialInstance->SetScalarParameterValue(FName("RadianValue"), NewRadius);
	}
}




