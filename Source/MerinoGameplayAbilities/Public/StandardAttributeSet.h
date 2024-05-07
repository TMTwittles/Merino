// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "StandardAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class MERINOGAMEPLAYABILITIES_API UStandardAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category="Health")
	FGameplayAttributeData Health;
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Health);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Health);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UStandardAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	GAMEPLAYATTRIBUTE_VALUE_GETTER(MaxHealth);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(MaxHealth);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(MaxHealth);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UStandardAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Damage);
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Damage);
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Damage);
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UStandardAttributeSet, Damage);
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
