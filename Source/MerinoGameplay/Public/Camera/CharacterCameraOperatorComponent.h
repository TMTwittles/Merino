// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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

	UPROPERTY(EditAnywhere, Category = FreeLookCameraSettings, meta = (AllowPrivateAccess="true"))
	float CharacterZOffset;

	UPROPERTY(BlueprintReadOnly, Category=OperatorDetails, meta = (AllowPrivateAccess="true"))
	FVector CalculatedLocation;

	UPROPERTY(BlueprintReadOnly, Category=OperatorDetails, meta = (AllowPrivateAccess="true"))
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

private:
	// Operates the camera, should be called every frame. 
	void OperateCamera();

		
};
