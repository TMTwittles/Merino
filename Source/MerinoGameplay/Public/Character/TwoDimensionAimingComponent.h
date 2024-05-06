// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TwoDimensionAimingComponent.generated.h"

/*
* Handles the twin stick aiming for a character based off input. Additional functionality includes linetracing for enemies, determining hits etc. 
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MERINOGAMEPLAY_API UTwoDimensionAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "AimInfo", meta = (AllowPrivateAccess="true"))
	FVector AimDirection;

	UPROPERTY(BlueprintReadOnly, Category = "AimInfo", meta = (AllowPrivateAccess="true"))
	FRotator AimRotation;

public:	
	// Sets default values for this component's properties
	UTwoDimensionAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void UpdateAimDirection(const FVector& InAimDirection);
	void SetAimRotation(const FRotator& InAimRotation);
	void AddYaw(const float YawInc);
	void AddPitch(const float PitchInc);
	UFUNCTION(BlueprintPure)
	FVector GetAimDirection() const;
	UFUNCTION(BlueprintPure)
	FRotator GetAimRotation() const;
};
