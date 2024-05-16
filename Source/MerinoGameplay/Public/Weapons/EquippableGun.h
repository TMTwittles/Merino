// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/EquipableWeapon.h"
#include "EquippableGun.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class MERINOGAMEPLAY_API AEquippableGun : public AEquipableWeapon
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GunAttribute, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> MuzzleLocation;

public:
	AEquippableGun();

	UFUNCTION(BlueprintCallable)
	void FireGun();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TriggerFireGunVFX();
	void TriggerFireGunVFX_Implementation();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FTransform GetMuzzleTransform() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CalculateBulletImpactPoints();
	void CalculateBulletImpactPoints_Implementation();
};
