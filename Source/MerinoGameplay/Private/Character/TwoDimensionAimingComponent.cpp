// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TwoDimensionAimingComponent.h"

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

	// ...
}

void UTwoDimensionAimingComponent::UpdateAimDirection(FVector AimInput)
{
	AimDirection = AimInput;
}

FVector UTwoDimensionAimingComponent::GetAimDirection() const
{
	return AimDirection;
}

