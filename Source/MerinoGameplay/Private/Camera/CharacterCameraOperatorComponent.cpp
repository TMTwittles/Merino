// Fill out your copyright notice in the Description page of Project Settings.
#include "Camera/CharacterCameraOperatorComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/TwoDimensionAimingComponent.h"
#include "MerinoGameplay.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"

// Sets default values for this component's properties
UCharacterCameraOperatorComponent::UCharacterCameraOperatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CalculatedLocation = FVector::Zero();
	TargetLocation = FVector::Zero();
	CalculatedRotation = FRotator::ZeroRotator;
	TargetRotation = FRotator::ZeroRotator;
}


// Called when the game starts
void UCharacterCameraOperatorComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get component dependencies.
	const APawn* PawnOwner = Cast<APawn>(GetOwner());
	if (PawnOwner != nullptr && PawnOwner->GetController() != nullptr)
	{
		Controller = PawnOwner->GetController();
	}
	else
	{
		UE_LOG(LogTemplateGameplayInvalidConfig, Error, TEXT("%s: Failed to access controller component in %s"), *GetNameSafe(this), *GetNameSafe(GetOwner()));
		return;
	}

	CameraSpringArm = GetOwner()->GetComponentByClass<USpringArmComponent>();
	if (CameraSpringArm == nullptr)
	{
		UE_LOG(LogTemplateGameplayInvalidConfig, Error, TEXT("%s: Failed to access camera boom component in %s"), *GetNameSafe(this), *GetNameSafe(GetOwner()));
		return;
	}
}


// Called every frame
void UCharacterCameraOperatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	OperateCamera(DeltaTime);
}

void UCharacterCameraOperatorComponent::SetCameraOperationMode(ECameraOperationMode InCameraOperationMode)
{
	ActiveMode = InCameraOperationMode;

	// Set up camera for the specifics of the camera operation mode. 
	switch (ActiveMode)
	{
	case ECameraOperationMode::FreeLook:
		EnterFreeLookCameraMode();
		break;
	case ECameraOperationMode::Aim:
		EnterAimCameraMode();
		break;
	case ECameraOperationMode::HipFire:
		EnterHipFireCameraMode();
		break;
	default:
		UE_LOG(LogTemplateGameplayInvalidConfig, Warning, TEXT("No enter function for mode: %s"), *UEnum::GetValueAsString(ActiveMode));
		break;
	}
}

void UCharacterCameraOperatorComponent::OperateCamera(float DeltaTime)
{
	if (CameraSpringArm == nullptr)
	{
		return;
	}

	if (CalculatedLocation == FVector::Zero())
	{
		CalculatedLocation = CameraSpringArm->GetRelativeLocation();
	}
	
	// Update calculated location based off the active camera operation mode.
	switch (ActiveMode)
	{
		case ECameraOperationMode::FreeLook:
			CalculateFreeLookCameraPosition();
			break;
		case ECameraOperationMode::Aim:
			CalculateAimCameraPosition();
			break;
		case ECameraOperationMode::HipFire:
			CalculateHipFireCameraPosition();
			break;
		default:
			UE_LOG(LogTemplateGameplayInvalidConfig, Error, TEXT("Unable to operate camera with mode: %s"), *UEnum::GetValueAsString(ActiveMode));
			break;
	}

	const FQuat CalculatedRotationQuat = CalculatedRotation.Quaternion();
	const FQuat TargetRotationQuat = TargetRotation.Quaternion();
	CalculatedRotation = FQuat::Slerp(CalculatedRotationQuat, TargetRotationQuat, CameraSlerpSpeed * DeltaTime).Rotator();
	CameraSpringArm->SetRelativeRotation(CalculatedRotation);
	CalculatedLocation = FMath::Lerp(CalculatedLocation, TargetLocation, CameraLerpSpeed * DeltaTime);
	CameraSpringArm->SetRelativeLocation(CalculatedLocation);
}

void UCharacterCameraOperatorComponent::EnterFreeLookCameraMode()
{
	
}

void UCharacterCameraOperatorComponent::EnterHipFireCameraMode()
{
}

void UCharacterCameraOperatorComponent::EnterAimCameraMode()
{
	
}

void UCharacterCameraOperatorComponent::CalculateFreeLookCameraPosition()
{
	// TODO: This is still prototype code, neccessary optimisation will obviously be made here.
	FVector ActorLocation = GetOwner()->GetActorLocation() + FVector(0.0f, 0.0f, FreeLookCharacterZOffset);
	FVector CharacterVelocity = GetOwner()->GetComponentByClass<UCharacterMovementComponent>()->Velocity;
	if (Controller != nullptr)
	{
		TargetRotation = Controller->GetControlRotation();
	}
	TargetLocation = ActorLocation + CharacterVelocity.GetSafeNormal() * CharacterVelocityXOffset;
	CameraSlerpSpeed = FreeLookCameraSlerpSpeed;
	CameraLerpSpeed = FreeLookCameraLerpSpeed;
}

void UCharacterCameraOperatorComponent::CalculateHipFireCameraPosition()
{
	//// TODO: This is still prototype code, neccessary optimisation will obviously be made here.
	//FVector ActorLocation = GetOwner()->GetActorLocation() - GetOwner()->GetActorForwardVector() * HipFireCharacterZOffset;
	//FVector AimOffset = GetOwner()->GetComponentByClass<UTwoDimensionAimingComponent>()->GetAimDirection() * CharacterAimXOffset;
	//TargetRotation.Yaw = GetOwner()->GetComponentByClass<UTwoDimensionAimingComponent>()->GetAimRotation().Yaw;
	//TargetLocation = ActorLocation + AimOffset;
	//// NOTICE: We never set the target rotation, this is because the player has no control over rotating the camera in aim mode thus
	//// we would use the existing target rotation from a previous mode that allowed modifying the target rotation. 
	//CameraSlerpSpeed = HipFireCameraSlerpSpeed;
	//CameraLerpSpeed = HipFireCameraLerpSpeed;
}

void UCharacterCameraOperatorComponent::CalculateAimCameraPosition()
{
	//// TODO: This is still prototype code, neccessary optimisation will obviously be made here.
	//FVector ActorLocation = GetOwner()->GetActorLocation() - GetOwner()->GetActorForwardVector() * AimCharacterZOffset;
	//FVector AimOffset = GetOwner()->GetComponentByClass<UTwoDimensionAimingComponent>()->GetAimDirection() * CharacterAimXOffset;
	//TargetRotation.Yaw = GetOwner()->GetComponentByClass<UTwoDimensionAimingComponent>()->GetAimRotation().Yaw;
	//TargetLocation = ActorLocation + AimOffset;
	//// NOTICE: We never set the target rotation, this is because the player has no control over rotating the camera in aim mode thus
	//// we would use the existing target rotation from a previous mode that allowed modifying the target rotation. 
	//CameraSlerpSpeed = AimCameraSlerpSpeed;
	//CameraLerpSpeed = AimCameraLerpSpeed;
}

ECameraOperationMode UCharacterCameraOperatorComponent::GetActiveCameraOperationMode() const
{
	return ActiveMode;
}

FRotator UCharacterCameraOperatorComponent::GetCurrentCameraRotation() const
{
	// The calculated rotation is always the current rotation.
	return CalculatedRotation;
}



