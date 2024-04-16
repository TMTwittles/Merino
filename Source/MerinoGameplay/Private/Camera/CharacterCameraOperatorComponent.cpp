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
}


// Called when the game starts
void UCharacterCameraOperatorComponent::BeginPlay()
{
	Super::BeginPlay();

	CameraSpringArm = GetOwner()->GetComponentByClass<USpringArmComponent>();
	if (CameraSpringArm == nullptr)
	{
		UE_LOG(LogTemplateGameplayInvalidComponent, Error, TEXT("%s: Failed to access camera boom component in %s"), *GetNameSafe(this), *GetNameSafe(GetOwner()));
	}
}


// Called every frame
void UCharacterCameraOperatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	OperateCamera();
}

void UCharacterCameraOperatorComponent::OperateCamera()
{
	if (CameraSpringArm == nullptr)
	{
		return;
	}

	CalculatedLocation = GetOwner()->GetActorLocation() + FVector(0.0f, 0.0f, CharacterZOffset);
	CameraSpringArm->SetRelativeLocation(CalculatedLocation);
}

