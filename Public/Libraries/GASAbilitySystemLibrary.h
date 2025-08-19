// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GASAbilitySystemLibrary.generated.h"

class UAbilitySystemComponent;
class UCharacterClassInfo;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class GFANTASY_API UGASAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/*ĳ���� Info ������ GM�� ���ؼ� �ϵ��� ���� ���̺귯�� �Լ�*/
	UFUNCTION(BlueprintPure)
	static UCharacterClassInfo* GetCharacterClassDefaultInfo(const UObject* WorldContextObject);
	
	/*�κ��丮���� ������ ã�� ���� ���ø� �Լ�*/
	template<typename T>
	static T* GetDataTableRowByTag(UDataTable* DataTable, FGameplayTag Tag);

	/**
	 * <summary>
	 * �ڱ� �ڽſ��� Effect�� �����Ѵ�
	 * </summary>
	 * <param name="SelfActor">����Ʈ�� ������ ����</param>
	 * <param name="Effect">������ Effect</param>
	 * <param name="Level">Effect Level</param>
	 * <returns>���� ����(����Ʈ�� Instant�� ��� ���뿡 �����߾ false�� ��ȯ��)</returns>
	 */
	UFUNCTION(BlueprintCallable, Category="GAS Library")
	static bool ApplyGASEffectToSelf(AActor* SelfActor, TSubclassOf<UGameplayEffect> Effect, float Level = 1.f);

	/**
	 * <summary>
	 * �ڱ� �ڽſ��� Effect�� �����Ѵ�
	 * </summary>
	 * <param name="SelfAbilitySystemComponent">����Ʈ�� ������ �����Ƽ �ý��� ������Ʈ</param>
	 * <param name="Effect">������ Effect</param>
	 * <param name="Level">Effect Level</param>
	 * <returns>���� ����(����Ʈ�� Instant�� ��� ���뿡 �����߾ false�� ��ȯ��)</returns>
	 */
	UFUNCTION(BlueprintCallable, Category="GAS Library")
	static bool ApplyGASEffectToSelfToASC(UAbilitySystemComponent* SelfAbilitySystemComponent, TSubclassOf<UGameplayEffect> Effect, float Level = 1.f);

	/**
	 * <summary>
	 * Ÿ�ο��� ����Ʈ�� �����Ѵ�
	 * </summary>
	 * <param name="SourceActor">����Ʈ�� ������Ų ����</param>
	 * <param name="TargetActor">����Ʈ�� ������ ����</param>
	 * <param name="Effect">������ Effect</param>
	 * <param name="Level">Effect Level</param>
	 * <returns>���� ����(����Ʈ�� Instant�� ��� ���뿡 �����߾ false�� ��ȯ��)</returns>
	 */
	UFUNCTION(BlueprintCallable, Category="GAS Library")
	static bool ApplyGASEffectToTarget(AActor* SourceActor, AActor* TargetActor, TSubclassOf<UGameplayEffect> Effect, float Level = 1.f);

	/**
	 * <summary>
	 * Ÿ�ο��� ����Ʈ�� �����Ѵ�
	 * </summary>
	 * <param name="SourceAbilitySystemComponent">����Ʈ�� ������Ų ����</param>
	 * <param name="TargetAbilitySystemComponent">����Ʈ�� ������ �����Ƽ �ý��� ������Ʈ</param>
	 * <param name="Effect">������ Effect</param>
	 * <param name="Level">Effect Level</param>
	 * <returns>���� ����(����Ʈ�� Instant�� ��� ���뿡 �����߾ false�� ��ȯ��)</returns>
	 */
	UFUNCTION(BlueprintCallable, Category="GAS Library")
	static bool ApplyGASEffectToTargetToASC(UAbilitySystemComponent* SourceAbilitySystemComponent, UAbilitySystemComponent* TargetAbilitySystemComponent, TSubclassOf<UGameplayEffect> Effect, float Level = 1.f);
	
	
};

template<typename T>
T* UGASAbilitySystemLibrary::GetDataTableRowByTag(UDataTable* DataTable, FGameplayTag Tag)
{
	/*Tag�� ������� �������� ã��*/
	return DataTable->FindRow<T>(Tag.GetTagName(), FString(""));
}
