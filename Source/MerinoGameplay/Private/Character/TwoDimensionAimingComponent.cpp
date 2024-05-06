// Fill out your copyright notice in the Description page of Project Settings.
#include "Character/TwoDimensionAimingComponent.h"
#include "MerinoDebugStatics.h"

// Sets default values for this component's properties
UTwoDimensionAimingComponent::UTwoDimensionAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UTwoDimensionAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UTwoDimensionAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AimDirection = AimRotation.Vector();
	UMerinoDebugStatics::DrawSingleFrameDebugLine(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + AimDirection * 2000.0f, FColor::Red);
	int NumCircles = 10;
	FVector Start = GetOwner()->GetActorLocation();
	float StepAmount = 2000.0f / NumCircles;
	float CurrStepAmount = StepAmount;
	for (int i = 0; i < NumCircles; i++)
	{
		UMerinoDebugStatics::DrawSingleFrameDebugSphere(GetWorld(), Start + CurrStepAmount * AimDirection, 25.0f, FColor::Green);
		CurrStepAmount += StepAmount;
	}
}

void UTwoDimensionAimingComponent::UpdateAimDirection(const FVector& UpdatedAimDirection)
{
	AimDirection = UpdatedAimDirection;
}

void UTwoDimensionAimingComponent::SetAimRotation(const FRotator& InAimRotation)
{
	AimRotation = InAimRotation;
}

void UTwoDimensionAimingComponent::AddYaw(const float YawInc)
{
	AimRotation.Yaw += YawInc;
}

void UTwoDimensionAimingComponent::AddPitch(const float PitchInc)
{
	AimRotation.Pitch += PitchInc;
}

FVector UTwoDimensionAimingComponent::GetAimDirection() const
{
	return AimDirection;
}

FRotator UTwoDimensionAimingComponent::GetAimRotation() const
{
	return AimRotation;
}

