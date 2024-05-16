// Fill out your copyright notice in the Description page of Project Settings.

#include "StandardAttributeSet.h"
#include "GameplayEffectExtension.h"

void UStandardAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		// Ensure health value never goes below zero.
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
}

void UStandardAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		const float DamageDone = GetDamage();
		// To prevent damage affects persisting, set to 0.
		SetDamage(0.0f);

		const float DamageAffectedHealth = GetHealth() - DamageDone;
		SetHealth(FMath::Clamp(DamageAffectedHealth, 0.0f, GetMaxHealth()));
	}
}
