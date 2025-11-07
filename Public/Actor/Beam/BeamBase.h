// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BeamBase.generated.h"


class ABeamSplineBase;
class AGASCombatNPC;
class UParticleSystem;
class USceneComponent;
class UParticleSystemComponent;
class UGameplayEffect;

UCLASS()
class GFANTASY_API ABeamBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABeamBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void SetBeamLocation();

	virtual void DetectedObject();

	virtual void SetStartAndEndPoint();

public:
	UFUNCTION()
	void PopFrontActor();

public:
	UFUNCTION(BlueprintCallable, Category = "BeamBase")
	virtual void ChangeTargetActor(AActor* NewTargetActor);

	UFUNCTION(BlueprintCallable, Category = "BeamBase")
	virtual void BeamEnd();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "BeamBase")
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "BeamBase")
	TObjectPtr<UParticleSystemComponent> BeamBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "BeamBase")
	TObjectPtr<UParticleSystemComponent> BeamExplosion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Replicated, Category = "BeamBase")
	UParticleSystem* BeamBodyParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Replicated, Category = "BeamBase")
	UParticleSystem* BeamExplosionParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Replicated, Category = "BeamBase")
	AGASCombatNPC* BeamOwnerActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Replicated, Category = "BeamBase")
	bool bTargetIsActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Replicated, Category = "BeamBase")
	AActor* TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Replicated, Category = "BeamBase")
	ABeamSplineBase* BeamSplineActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Replicated, Category = "BeamBase")
	float Duration;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Replicated, Category = "BeamBase")
	FName BeamStartSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Replicated, Category = "BeamBase")
	FVector StartMultiply;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "BeamBase")
	FVector BeamStartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "BeamBase")
	FVector BeamEndLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Replicated, Category = "BeamBase")
	float BeamRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Replicated, Category = "BeamBase")
	float BeamHalfHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Replicated, Category = "BeamBase")
	TArray<TEnumAsByte<EObjectTypeQuery>> DetectObjectType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Replicated, Category = "BeamBase")
	TArray<AActor*> DetectedActorsToIgnore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Replicated, Category = "BeamBase")
	bool DetectedIgnoreSelf;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Replicated, Category = "BeamBase")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "BeamBase")
	float ElapsedTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "BeamBase")
	TArray<AActor*> DetectedActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "BeamBase")
	float DamageTick = 0.7f;
};
