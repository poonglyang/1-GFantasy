// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GameplayEffect/GameplayEffectExecutionCalculation/DamageExecutionCalc.h"

#include "GAS/AttributeSet/GASCharacterAS.h"
#include "GAS/AttributeSet/GASCombatAS.h"


UDamageExecutionCalc::UDamageExecutionCalc()
{
	// �ҽ�(Instigator) �� attribute ĸó / �ҽ� -> �����Ƽ �������� �Ӽ�
	AttackPowerDef = FGameplayEffectAttributeCaptureDefinition(
		UGASCombatAS::GetAttackPowerAttribute(),
		EGameplayEffectAttributeCaptureSource::Source, true);

	CritChanceDef = FGameplayEffectAttributeCaptureDefinition(
		UGASCombatAS::GetCriticalChanceAttribute(),
		EGameplayEffectAttributeCaptureSource::Source, true);

	CritDamageDef = FGameplayEffectAttributeCaptureDefinition(
		UGASCombatAS::GetCriticalDamageAttribute(),
		EGameplayEffectAttributeCaptureSource::Source, true);

	// ��꿡�� ������ �Ӽ� ����Ʈ�� �߰�
	RelevantAttributesToCapture.Add(AttackPowerDef);
	RelevantAttributesToCapture.Add(CritChanceDef);
	RelevantAttributesToCapture.Add(CritDamageDef);
}

void UDamageExecutionCalc::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParams.SourceTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	// �Ӽ� �б� : �̸� ĸó�� �Ӽ� ��������
	float AttackPower = 0.f;
	float CritChance = 0.f;
	float CritDamage = 0.f;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(AttackPowerDef, EvaluateParams, AttackPower);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CritChanceDef, EvaluateParams, CritChance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CritDamageDef, EvaluateParams, CritDamage);

	// �����Ƽ���� �Ѱ��� SkillRatio ��������. ( �⺻�� 1.0 )
	float SkillRatio = Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("Data.SkillRatio"),true,1.0f);

	// ������ ��� ��ų ��� ���ϱ�
	float RawDamage = AttackPower * SkillRatio;

	// ũ��Ƽ�� Ȯ�� ����
	const bool bIsCriticalHit = FMath::FRand() <= CritChance;
	if (bIsCriticalHit)
	{
		// ġ��Ÿ �±� �߰�
		RawDamage *= CritDamage;
	}

	// Ÿ���� Health Attribute�� ���� (Additive ���)
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
		UGASCharacterAS::GetHealthAttribute(),
		EGameplayModOp::Additive,
		-RawDamage));	// ���ط��̹Ƿ� ����
	
}
