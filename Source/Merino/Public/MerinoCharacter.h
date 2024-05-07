// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "EquipableWeapon.h"
#include "AbilitySystemInterface.h"
#include "MerinoCharacter.generated.h"

class UAbilitySystemComponent;
class UGameplayAbility;
class UStandardAttributeSet;
class UCharacterCameraOperatorComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UTwoDimensionAimingComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AMerinoCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = GameplayAbilitySystem, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = GameplayAbilitySystem, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStandardAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayAbilitySystem, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> GameplayAbilities;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CameraComponents, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCharacterCameraOperatorComponent> CameraOperatorComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;


	// TODO: Need to rename Aiming action to something more appropriate like ADS, if we arent aiming but we are shooting
	// then we are hip firing etc. Rename this to make things less confusing. 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> StartAimingAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> AimingAction;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ShootingAction;

	// TODO: Use of this variable is temporary, will be phased out once moving logic to more of a state machine. 
	UPROPERTY(BlueprintReadOnly, Category = Shooting, meta = (AllowPrivateAccess = "true"))
	uint8 bIsShooting;

	// TODO: Use of this variable is temporary, will be phased out once moving logic to more of a state machine. 
	UPROPERTY(BlueprintReadOnly, Category = Aiming, meta = (AllowPrivateAccess = "true"))
	uint8 bIsAiming;

	UPROPERTY(BlueprintReadOnly, Category = Aiming, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UTwoDimensionAimingComponent> AimingComp;

	UPROPERTY(BlueprintReadOnly, Category= WeaponSettings, meta = (AllowPrivateAccess= "true"))
	TObjectPtr<AEquipableWeapon> EquipedWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= WeaponSettings, meta = (AllowPrivateAccess= "true"))
	TSubclassOf<AEquipableWeapon> WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WeaponSettings, meta = (AllowPrivateAccess= "true"))
	FName WeaponAttachmentSocket;
	
public:
	AMerinoCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// To add mapping context
	virtual void BeginPlay();
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

private:
	void GrantAbilities();

	/** Called when aim input started */
	void EnterAim(const FInputActionValue& Value);

	/** Called when aim input released */
	void ExitAim(const FInputActionValue& Value);

	/** Called when fire input started */
	void StartShooting(const FInputActionValue& Value);

	/** Called when fire input released */
	void ExitShooting(const FInputActionValue& Value);

	/** Read input from player to have character aim weapon. */
	void Aim(const FInputActionValue& Value);

	// TODO: These functions demonstrate the need to seperate this logic into a state machine.
	/** Handles entering aiming or shooting */
	void EnterAimingOrShooting();

	/** Handles the exit when aiming or shooting */
	void ExitAimingOrShooting();

	void SpawnWeapon();

public:
	/** Determines if character is aiming weapon or not */
	UFUNCTION(BlueprintPure)
	bool IsAiming() const;

	/** Determines if character is firing weapon or not */
	UFUNCTION(BlueprintPure)
	bool IsFiring() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AEquipableWeapon* GetEquippedWeapon() const;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void SetControlRotationToDirection(const FVector TargetDirection);
};

