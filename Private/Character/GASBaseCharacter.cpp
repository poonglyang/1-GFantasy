// Fill out your copyright notice in the Description page of Project Settings.
#include "Character/GASBaseCharacter.h"
#include "PlayerState/GASBasePlayerState.h"

// Sets default values
AGASBaseCharacter::AGASBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGASBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGASBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGASBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AGASBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

UAbilitySystemComponent* AGASBaseCharacter::GetAbilitySystemComponent() const
{
	// ���� ASC ������Ʈ�� PlayerState�� �ִ� ���
	if (const AGASBasePlayerState* PS = GetPlayerState<AGASBasePlayerState>())
	{
		return PS->GetAbilitySystemComponent();
	}

	return nullptr;
}


