// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraOperationMode.h"
#include "CharacterCameraOperatorComponent.generated.h"

class USpringArmComponent;

/**
* Controls and operates the camera, for now just lazily access the spring arm component and sets it to the location
* of the actor. Eventually should be able to operate on different modes, access player input and other actions that involve
* manipulating / operating the player camera. 
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MERINOGAMEPLAY_API UCharacterCameraOperatorComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = SharedCameraSettings, meta = (AllowPrivateAccess="true"))
	float CharacterZOffset;

	UPROPERTY(EditAnywhere, Category = SharedCameraSettings, meta = (AllowPrivateAccess="true"))
	float CameraLerpSpeed;

	UPROPERTY(EditAnywhere, Category = AimCameraSettings, meta = (AllowPrivateAccess = "true"))
	float CharacterAimXOffset;

	UPROPERTY(BlueprintReadOnly, Category=OperatorConfig, meta=(AllowPrivateAccess="true"))
	TEnumAsByte<ECameraOperationMode> ActiveMode;
	UPROPERTY(BlueprintReadOnly, Category=OperatorConfig, meta = (AllowPrivateAccess="true"))
	FVector TargetLocation;
	UPROPERTY(BlueprintReadOnly, Category=OperatorConfig, meta = (AllowPrivateAccess="true"))
	FVector CalculatedLocation;
	UPROPERTY(BlueprintReadOnly, Category=OperatorConfig, meta = (AllowPrivateAccess="true"))
	TObjectPtr<USpringArmComponent> CameraSpringArm;

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
	// Calculates camera position when in free look camera operation mode. TODO: This function should add functionality for reading player input. 
	void CalculateFreeLookCameraPosition();
	// Calculates camera position when in aiming camera operation mode.
	void CalculateAimCameraPosition();
		
};
