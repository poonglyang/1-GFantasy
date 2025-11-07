// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeamSplineBase.generated.h"

class USplineComponent;

UCLASS()
class GFANTASY_API ABeamSplineBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABeamSplineBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "BeamSplineBase")
	TObjectPtr<USplineComponent> BeamSplineComponent;
	
};
