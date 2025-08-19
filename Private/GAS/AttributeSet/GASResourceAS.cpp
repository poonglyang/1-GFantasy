// Fill out your copyright notice in the Description page of Project Settings.
#include "GAS/AttributeSet/GASResourceAS.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GAS/AbilitySystemComponent/PlayerCharacterGASC.h"

void UGASResourceAS::OnRep_LimitGage(const FGameplayAttributeData& OldLimitGage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASResourceAS, LimitGage, OldLimitGage);
}

void UGASResourceAS::OnRep_MaxLimitGage(const FGameplayAttributeData& OldMaxLimitGage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASResourceAS, MaxLimitGage, OldMaxLimitGage);
}

void UGASResourceAS::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetLimitGageAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxLimitGage());
	}

}

void UGASResourceAS::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// limit Gage Clamp Àû¿ë
	if (Data.EvaluatedData.Attribute == GetLimitGageAttribute())
	{
		SetLimitGage(FMath::Clamp(GetLimitGage(), 0.f, GetMaxLimitGage()));
		
		const float NewValue = GetLimitGage();
		if (UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent())
		{
			if (UPlayerCharacterGASC* PlayerASC = Cast<UPlayerCharacterGASC>(ASC))
			{
				PlayerASC->OnLimitGageChanged.ExecuteIfBound(NewValue);
			}
		}
	}
}

void UGASResourceAS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGASResourceAS, LimitGage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASResourceAS, MaxLimitGage, COND_None, REPNOTIFY_Always);

} 
