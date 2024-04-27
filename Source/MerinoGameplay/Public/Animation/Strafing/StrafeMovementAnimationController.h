// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StrafeMovementAnimationController.generated.h"


UENUM(BlueprintType)
enum class EStrafeDirection : uint8 {
    NONE UMETA(DisplayName="None"),
    FORWARD UMETA(DisplayName = "Forward"),
    LEFT UMETA(DisplayName = "Left"),
    RIGHT UMETA(DisplayName = "Right"),
    BACKWARD UMETA(DisplayName = "Backward")
};

USTRUCT(BlueprintType)
struct FStrafeAnimationMovementRange
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere)
    float MinDegrees;
    UPROPERTY(EditAnywhere)
    float MixDegrees;
};

USTRUCT(BlueprintType)
struct FStrafeAnimation
{
    GENERATED_USTRUCT_BODY()

    // Movement ranges to trigger the animation. Stored as array 
    // to allow multiple ranges, i.e -180 - -90, 90 - 180.
    UPROPERTY(EditAnywhere)
    TArray<FStrafeAnimationMovementRange> MovementRanges;
    
    // Threshold strafe animation can play before need to change.
    // If movement range is -45 to 45 degrees and threshold is 1.25f, then if movement will need
    // exceed the threshold of -56.25 to 56.25 degrees before needing to change strafe animation.
    UPROPERTY(EditAnywhere)
    float ChangeStrafeDirectionThresholdAmount;
};

/**
 * Object for operation strafe movement, allows setting thresholds for directions and 
 * provides access to different animations per direction. 
 */
UCLASS(BlueprintType)
class MERINOGAMEPLAY_API UStrafeMovementAnimationController : public UObject
{
	GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StrafeAnimations, meta = (AllowPrivateAccess = "True"))
    FStrafeAnimation ActiveStrafeAnimation;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StrafeAnimations, meta = (AllowPrivateAccess = "True"))
    FStrafeAnimation PreviousStrafeAnimation;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StrafeAnimations, meta = (AllowPrivateAccess= "True"))
    uint8 bShouldPivot;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=StrafeAnimations, meta=(AllowPrivateAccess="True"))
    TArray<FStrafeAnimation> StrafeAnimations;
public:
    UFUNCTION(BlueprintCallable)
    void AddDirections(TArray<FStrafeAnimation> InStrafeAnimations);
    UFUNCTION(BlueprintCallable)
    void EvaluateActiveStrafeAnimation(float InStrafeDirectionDegrees);
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool ShouldPivot() const;
private:
    bool StrafeAnimationInPriorityRange(const FStrafeAnimation& StrafeAnimation, const float DirectionDegrees) const;
    bool StrafeAnimationInRange(const FStrafeAnimation& StrafeAnimation, const float DirectionDegrees) const;

};
