// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "MerinoCharacter.generated.h"

class UCharacterCameraOperatorComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UTwoDimensionAimingComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AMerinoCharacter : public ACharacter
{
	GENERATED_BODY()

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

public:
	AMerinoCharacter();

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

public:
	/** Determines if character is aiming weapon or not */
	UFUNCTION(BlueprintPure)
	bool IsAiming() const;

	/** Determines if character is firing weapon or not */
	UFUNCTION(BlueprintPure)
	bool IsFiring() const;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void SetControlRotationToDirection(const FVector TargetDirection);
};

