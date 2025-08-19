// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilities/Public/AbilitySystemComponent.h"
#include "GameplayAbilities/Public/AttributeSet.h"
#include "GASCombatAS.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class GFANTASY_API UGASCombatAS : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	virtual void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower);

	UFUNCTION()
	virtual void OnRep_Defense(const FGameplayAttributeData& OldDefense);

	UFUNCTION()
	virtual void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed);

	UFUNCTION()
	virtual void OnRep_CriticalChance(const FGameplayAttributeData& OldCriticalChance);

	UFUNCTION()
	virtual void OnRep_CriticalDamage(const FGameplayAttributeData& OldCriticalDamage);

public:
	// ���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", ReplicatedUsing = OnRep_AttackPower)
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UGASCombatAS, AttackPower)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", ReplicatedUsing = OnRep_Defense)
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UGASCombatAS, Defense)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", ReplicatedUsing = OnRep_AttackSpeed)
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UGASCombatAS, AttackSpeed)

	// ġ��Ÿ Ȯ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", ReplicatedUsing = OnRep_CriticalChance)
	FGameplayAttributeData CriticalChance;
	ATTRIBUTE_ACCESSORS(UGASCombatAS, CriticalChance)

	// ġ��Ÿ ���ط�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", ReplicatedUsing = OnRep_CriticalDamage)
	FGameplayAttributeData CriticalDamage;
	ATTRIBUTE_ACCESSORS(UGASCombatAS, CriticalDamage)
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	
};
