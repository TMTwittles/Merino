// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquipableWeapon.generated.h"

/*
* Actor for the weapon that a pawn can hold / use. Contains components for the weapon visuals and where to hold
* the weapon.
*/
UCLASS(BlueprintType, Blueprintable, Abstract)
class MERINOGAMEPLAY_API AEquipableWeapon : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WeaponAttachPoint, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> WeaponAttachPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= WeaponAttachPoint, meta= (AllowPrivateAccess="true"))
	TObjectPtr<USceneComponent> MeshAttachPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= WeaponVisuals, meta=(AllowPrivateAccess= "true"))
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= WeaponAttachPoint, meta=(AllowPrivateAccess= "true"))
	TObjectPtr<USceneComponent> IKWeaponAttachPoint; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttachmentConfig, meta = (AllowPrivateAccess = "true"))
	FTransform WeaponAttachPointRelativeTransform;

public:	
	// Sets default values for this actor's properties
	AEquipableWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Called once the weapon has been attached to owning pawn.
	void ConfigureWeaponPostAttachment();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FTransform GetIKWeaponAttachPoint() const;
};
