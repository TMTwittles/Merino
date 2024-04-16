// Fill out your copyright notice in the Description page of Project Settings.
#include "Camera/CharacterCameraOperatorComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MerinoGameplay.h"

// Sets default values for this component's properties
UCharacterCameraOperatorComponent::UCharacterCameraOperatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CalculatedLocation = FVector::Zero();
	TargetLocation = FVector::Zero();
}


// Called when the game starts
void UCharacterCameraOperatorComponent::BeginPlay()
{
	Super::BeginPlay();

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
		default:
			UE_LOG(LogTemplateGameplayInvalidConfig, Error, TEXT("Unable to operate camera with mode: %s"), *UEnum::GetValueAsString(ActiveMode.GetValue()));
			break;
	}

	CalculatedLocation = FMath::Lerp(CalculatedLocation, TargetLocation, CameraLerpSpeed * DeltaTime);
	CameraSpringArm->SetRelativeLocation(CalculatedLocation);
}

void UCharacterCameraOperatorComponent::CalculateFreeLookCameraPosition()
{
	TargetLocation = GetOwner()->GetActorLocation() + FVector(0.0f, 0.0f, CharacterZOffset);
}

void UCharacterCameraOperatorComponent::CalculateAimCameraPosition()
{
	FVector ActorLocation = GetOwner()->GetActorLocation() + FVector(0.0f, 0.0f, CharacterZOffset);
	FVector AimOffset = GetOwner()->GetActorForwardVector() * CharacterAimXOffset;
	TargetLocation = ActorLocation + AimOffset;
}

