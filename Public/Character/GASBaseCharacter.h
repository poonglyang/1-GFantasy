// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayAbilities/Public/AbilitySystemComponent.h"
#include "GAS/AbilitySystemComponent/GASCBase.h"
#include "AbilitySystemInterface.h"
#include "GASBaseCharacter.generated.h"

UCLASS()
class GFANTASY_API AGASBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGASBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

public:

	
};
