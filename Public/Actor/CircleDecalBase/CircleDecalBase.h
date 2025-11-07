// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CircleDecalBase.generated.h"

class UTimelineComponent;
class UMaterialInstanceDynamic;
class UCurveFloat;

UCLASS()
class GFANTASY_API ACircleDecalBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACircleDecalBase();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override ;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	void CreateDynamicMaterial();

public:
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "CircleDecalBase")
	void InitCircleDecal();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "CircleDecalBase")
	void SetDecalColor(FLinearColor Color);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "CircleDecalBase")
	void SetDecalRadius(float NewRadius);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "CircleDecalBase")
	void ChangeCircleDecal(UCurveFloat* Curve);

	UFUNCTION()
	void ChangeAreaDecalSize(float NewSize);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CircleDecalBase")
	TObjectPtr<UDecalComponent> Arc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CircleDecalBase")
	TObjectPtr<UDecalComponent> Area;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CircleDecalBase")
	UTimelineComponent* DecalAreaTimeline;
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Replicated, Category = "CircleDecalBase")
	UMaterialInstanceDynamic* ArcDynamicMaterialInstance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Replicated, Category = "CircleDecalBase")
	UMaterialInstanceDynamic* AreaDynamicMaterialInstance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, Category = "CircleDecalBase")
	float Radius;
};
