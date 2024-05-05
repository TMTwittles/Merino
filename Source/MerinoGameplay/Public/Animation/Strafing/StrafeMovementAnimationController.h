// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StrafeMovementAnimationController.generated.h"

// NOTE: Order of enums matter for construction. 
UENUM(BlueprintType)
enum class EStrafeDirection : uint8 {
    FORWARD UMETA(DisplayName = "Forward"),
    RIGHT UMETA(DisplayName = "Right"),
    BACKWARD UMETA(DisplayName = "Backward"),
    LEFT UMETA(DisplayName = "Left")
};

/*
* House the range for strafe movement. Note, all values are in degrees and positive.
* For example forward strafe direction would have a strafe direction of 0 with min range of 45 and max range of 315 degrees.
*/ 
USTRUCT()
struct FStrafeMovementRange
{
    GENERATED_USTRUCT_BODY()
    float StrafeDirectionDegrees;
    float StrafeDirectionDegreesUnwind;
    float StrafeRangeDegrees;
};

/**
 * Object for controlling strafe movement animations. 
 */
UCLASS(BlueprintType)
class MERINOGAMEPLAY_API UStrafeMovementAnimationController : public UObject
{
	GENERATED_BODY()
    
    UPROPERTY()
    TArray<FStrafeMovementRange> MovementRanges;
    UPROPERTY()
    int ActiveStrafeDirection;

public:

    UStrafeMovementAnimationController();
    UFUNCTION(BlueprintCallable)
    EStrafeDirection EvaluateActiveStrafeDirection(const float InMovementDirectionDegrees);
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetAngleRelativeToActiveStrafeDirection(const float InMovementDirectionDegrees) const;
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetStrafeDirectionDegrees(const EStrafeDirection InStrafeDirection) const;

private:
    void ConfigureMovementRanges();
    FStrafeMovementRange BuildStrafeMovementRange(const float InStrafeDirectionDegrees, const float InStrafeRangeDegrees) const;
    bool StrafeDirectionInRange(const int InStrafeDirection, const float InSignedDirectionDegrees) const;
    bool InvalidMovementDirection(const float InMovementDirectionDegrees) const;
    bool InNegativeRange(const FStrafeMovementRange& InMovementRange, const float InMovementDirectionDegrees) const;
    bool InPositiveRange(const FStrafeMovementRange& InMovementRange, const float InMovementDirectionDegrees) const;
};
