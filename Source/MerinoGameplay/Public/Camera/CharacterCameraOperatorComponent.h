// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraOperationMode.h"
#include "CharacterCameraOperatorComponent.generated.h"

class USpringArmComponent;
class AController;

/**
* Controls and operates the camera. 
* TODO: This should be renamed to PawnCameraOperatorComponent.
* TODO: This will need be a more state machine approach, that is sorta happening but aim modes should be modular
* and characteristics data oriented.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MERINOGAMEPLAY_API UCharacterCameraOperatorComponent : public UActorComponent
{
	GENERATED_BODY()

	// Free look camera settings.
	UPROPERTY(EditAnywhere, Category = FreeLookCameraSettings, meta = (AllowPrivateAccess="true"))
	float FreeLookCharacterZOffset;
	UPROPERTY(EditAnywhere, Category=FreeLookCameraSettings, meta = (AllowPrivateAccess = "true"))
	float FreeLookCameraLerpSpeed;
	UPROPERTY(EditAnywhere, Category = FreeLookCameraSettings, meta = (AllowPrivateAccess = "true"))
	float FreeLookCameraSlerpSpeed;
	UPROPERTY(EditAnywhere, Category = FreeLookCameraSettings, meta = (AllowPrivateAccess = "true"))
	float CharacterVelocityXOffset;

	// Hip fire camera settings
	UPROPERTY(EditAnywhere, Category = HipFireCameraSettings, meta = (AllowPrivateAccess = "true"))
	float HipFireCharacterZOffset;
	UPROPERTY(EditAnywhere, Category = HipFireCameraSettings, meta = (AllowPrivateAccess = "true"))
	float HipFireCameraLerpSpeed;
	UPROPERTY(EditAnywhere, Category = HipFireCameraSettings, meta = (AllowPrivateAccess = "true"))
	float HipFireCameraSlerpSpeed;
	UPROPERTY(EditAnywhere, Category = HipFireCameraSettings, meta = (AllowPrivateAccess = "true"))
	float CharacterHipFireXOffset;

	// Aim Camera settings
	UPROPERTY(EditAnywhere, Category = AimCameraSettings, meta = (AllowPrivateAccess = "true"))
	float AimCharacterZOffset;
	UPROPERTY(EditAnywhere, Category = AimCameraSettings, meta = (AllowPrivateAccess = "true"))
	float AimCameraLerpSpeed;
	UPROPERTY(EditAnywhere, Category = AimCameraSettings, meta = (AllowPrivateAccess = "true"))
	float AimCameraSlerpSpeed;
	UPROPERTY(EditAnywhere, Category = AimCameraSettings, meta = (AllowPrivateAccess = "true"))
	float CharacterAimXOffset;

	// Operator values
	UPROPERTY(BlueprintReadOnly, Category = OperatorValues, meta = (AllowPrivateAccess = "true"))
	FRotator CalculatedRotation;
	UPROPERTY(BlueprintReadOnly, Category = OperatorValues, meta = (AllowPrivateAccess= "true"))
	FRotator TargetRotation;
	UPROPERTY(BlueprintReadOnly, Category = OperatorValues, meta = (AllowPrivateAccess = "true"))
	FVector TargetLocation;
	UPROPERTY(BlueprintReadOnly, Category = OperatorValues, meta = (AllowPrivateAccess = "true"))
	FVector CalculatedLocation;
	UPROPERTY(BlueprintReadOnly, Category = OperatorValues, meta = (AllowPrivateAccess = "true"))
	float CameraLerpSpeed;
	UPROPERTY(BlueprintReadOnly, Category = OperatorValues, meta = (AllowPrivateAccess = "true"))
	float CameraSlerpSpeed;

	// Operator config
	UPROPERTY(BlueprintReadOnly, Category=OperatorConfig, meta=(AllowPrivateAccess="true"))
	TEnumAsByte<ECameraOperationMode> ActiveMode;
	UPROPERTY(BlueprintReadOnly, Category=OperatorConfig, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USpringArmComponent> CameraSpringArm;
	// Reference the PlayerController to access the control rotation.
	UPROPERTY(BlueprintReadOnly, Category=OperatorConfig, meta=(AllowPrivateAccess="true"))
	TObjectPtr<AController> Controller;

public:	
	// Sets default values for this component's properties
	UCharacterCameraOperatorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetCameraOperationMode(ECameraOperationMode InCameraOperationMode);
private:
	// Operates the camera, should be called every frame. 
	void OperateCamera(float DeltaTime);
	// Handles config when entering free look camera mode.
	void EnterFreeLookCameraMode();
	// Handles config when entering hip fire camera mode.
	void EnterHipFireCameraMode();
	// Handles config when entering aim camera mode. 
	void EnterAimCameraMode();
	// Calculates camera position when in free look camera operation mode. TODO: This function should add functionality for reading player input. 
	void CalculateFreeLookCameraPosition();
	// Calculates camera position when hip firing. 
	void CalculateHipFireCameraPosition();
	// Calculates camera position when in aiming camera operation mode.
	void CalculateAimCameraPosition();

public:

	UFUNCTION(BlueprintPure)
	ECameraOperationMode GetActiveCameraOperationMode() const;

	// As camera does not always follow the control rotation
	// use this method to determine input direction rather than controller rotation. 
	UFUNCTION(BlueprintPure)
	FRotator GetCurrentCameraRotation() const;
		
};
