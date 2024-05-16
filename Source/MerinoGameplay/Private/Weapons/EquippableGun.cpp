// Fill out your copyright notice in the Description page of Project Settings.
#include "Weapons/EquippableGun.h"
#include "Character/CharacterAimingComponent.h"

AEquippableGun::AEquippableGun() : AEquipableWeapon()
{
	MuzzleLocation = CreateDefaultSubobject<USceneComponent>("Muzzle");
	MuzzleLocation->SetupAttachment(WeaponMesh);
}

void AEquippableGun::FireGun()
{
	// Must calculate impact points before weapon fires. 
	CalculateBulletImpactPoints();
	TriggerFireGunVFX();
}

void AEquippableGun::TriggerFireGunVFX_Implementation()
{
}

FTransform AEquippableGun::GetMuzzleTransform() const
{
	return MuzzleLocation->GetComponentTransform();
}

void AEquippableGun::CalculateBulletImpactPoints_Implementation()
{
	
}