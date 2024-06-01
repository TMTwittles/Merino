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
    LEFT UMETA(DisplayName = "Left"),
    NONE UMETA(DisplayName = "NONE")
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
    float StrafeRangeLeft;
    float StrafeRangeRight;
};

/**
 * Object for controlling strafe movement animations. 
 */
UCLASS(BlueprintType)
class MERINOGAMEPLAY_API UStrafeMovementAnimationController : public UObject
{
	GENERATED_BODY()

    UPROPERTY()
    TMap<EStrafeDirection, FStrafeMovementRange> MovementRangesMap;
    UPROPERTY()
    TArray<FStrafeMovementRange> MovementRanges;
    UPROPERTY()
    EStrafeDirection ActiveStrafeDirection;

public:

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStrafeDirectionChanged, EStrafeDirection, NewDirection);
    UPROPERTY(BlueprintAssignable)
    FOnStrafeDirectionChanged StrafeDirectionChanged;

    UStrafeMovementAnimationController();
    UFUNCTION(BlueprintCallable)
    void EvaluateActiveStrafeDirection(const float InMovementDirectionDegrees);
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetAngleRelativeToActiveStrafeDirection(const float InMovementDirectionDegrees) const;
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetStrafeDirectionDegrees(const EStrafeDirection InStrafeDirection) const;
    // Establishes a movement for the inserted direction, using a clock wise direction as the starting point with left and right range.
    UFUNCTION(BlueprintCallable)
    void SetMovementRange(const EStrafeDirection InStrafeDirection, const float InClockwiseDirectionDegrees, const float InRangeDegreesLeft, const float InRangeDegreesRight);

private:
    float GetAngleRelativeToStrafeDirection(const EStrafeDirection InStrafeDirection, float InMovementDirectionDegrees) const;
    FStrafeMovementRange BuildStrafeMovementRange(const float InStrafeDirectionDegrees, const float InRangeDegreesLeft, const float InRangeDegreesRight) const;
    bool StrafeDirectionInRange(const EStrafeDirection Direction, const float InSignedDirectionDegrees) const;
    bool InvalidMovementDirection(const float InMovementDirectionDegrees) const;
    bool InNegativeRange(const FStrafeMovementRange& InMovementRange, const float InMovementDirectionDegrees) const;
    bool InPositiveRange(const FStrafeMovementRange& InMovementRange, const float InMovementDirectionDegrees) const;

public:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FORCEINLINE EStrafeDirection GetActiveStrafeDirection() const { return ActiveStrafeDirection; }
};
