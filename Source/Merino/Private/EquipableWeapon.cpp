// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipableWeapon.h"

// Sets default values
AEquipableWeapon::AEquipableWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponAttachPoint = CreateDefaultSubobject<USceneComponent>("Primary attach point");
	SetRootComponent(WeaponAttachPoint);
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("Weapon mesh");
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetupAttachment(WeaponAttachPoint);
	IKWeaponAttachPoint = CreateDefaultSubobject<USceneComponent>("IK attach point");
	IKWeaponAttachPoint->SetupAttachment(WeaponMesh);
}

// Called when the game starts or when spawned
void AEquipableWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEquipableWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEquipableWeapon::ConfigureWeaponPostAttachment()
{
	// Set the relative transform. 
	GetRootComponent()->SetRelativeTransform(WeaponAttachPointRelativeTransform);
}

FTransform AEquipableWeapon::GetIKWeaponAttachPoint() const
{
	return IKWeaponAttachPoint->GetComponentTransform();
}

