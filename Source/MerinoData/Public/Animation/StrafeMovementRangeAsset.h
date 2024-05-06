// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StrafeMovementRangeAsset.generated.h"

/*
* Struct housing the valid ranges in degrees for strafe movement.
*/
USTRUCT(BlueprintType)
struct FStrafeAnimationMovementRange
{
    GENERATED_USTRUCT_BODY()

    // Min and max degrees in which the strafe animation can play. These values
    // are evaluated when the character is not playing any strafe animation and determining 
    // which strafe animation to play first.
    UPROPERTY(EditAnywhere, Category = DefaultMovementRange)
    float MinDegrees;
    UPROPERTY(EditAnywhere, Category = DefaultMovementRange)
    float MaxDegrees;

    // Additional threshold amount which is to be added to the existing movement range. These
    // values are queried when the strafe animation is active and the controller is determining
    // when to change strafe directions. 
    UPROPERTY(EditAnywhere, Category = ThresholdMovementRange)
    float MinDegreesThreshold;
    UPROPERTY(EditAnywhere, Category = ThresholdMovementRange)
    float MaxDegreesThreshold;
};

/**
 * Asset the movement range for strafing, a ForwardStrafeMovementRangeAsset
 * would contain data about moving in a forward direction.
 */
UCLASS(BlueprintType)
class MERINODATA_API UStrafeMovementRangeAsset : public UDataAsset
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = DefaultMovementRange)
    TArray<FStrafeAnimationMovementRange> MovementRanges;
};
