// Fill out your copyright notice in the Description page of Project Settings.


#include "StandardAttributeSet.h"
#include "GameplayEffectExtension.h"

void UStandardAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
}

void UStandardAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

}
