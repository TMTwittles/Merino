// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StrafeMovementAnimationController.generated.h"

class UAnimSequence;
class UBlendSpace;

UENUM(BlueprintType)
enum class EStrafeDirection : uint8 {
    NONE UMETA(DisplayName="None"),
    FORWARD UMETA(DisplayName = "Forward"),
    LEFT UMETA(DisplayName = "Left"),
    RIGHT UMETA(DisplayName = "Right"),
    BACKWARD UMETA(DisplayName = "Backward")
};

USTRUCT(BlueprintType)
struct FStrafeAnimation
{
    GENERATED_USTRUCT_BODY()

    // Priority ranges
    UPROPERTY(EditAnywhere, Category = StrafePriorityRange)
    float PriorityMinDegrees;
    UPROPERTY(EditAnywhere, Category = StrafePriorityRange)
    float PriorityMaxDegrees;

    // Valid ranges
    UPROPERTY(EditAnywhere, Category = StrafeDefaultRange)
    float MinDegrees;
    UPROPERTY(EditAnywhere, Category = StrafeDefaultRange)
    float MaxDegrees;

    // Animations
    UPROPERTY(EditAnywhere, Category = StrafeAnimation)
    TObjectPtr<UAnimSequence> TransitionAnim;
    UPROPERTY(EditAnywhere, Category = StrafeAnimation)
    TObjectPtr<UAnimSequence> LocomotionAnim;
    UPROPERTY(EditAnywhere, Category = StrafeAnimation)
    TObjectPtr<UBlendSpace> StrafeMovementBS;
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
    UAnimSequence* GetActiveStrafeTransitionAnim() const;
    UFUNCTION(BlueprintCallable, BlueprintPure)
    UAnimSequence* GetActiveStrafeLocomotionAnim() const;
    UFUNCTION(BlueprintCallable, BlueprintPure)
    UBlendSpace* GetActiveStrafeBlendSpace() const;
    UFUNCTION(BlueprintCallable, BlueprintPure)
    UAnimSequence* GetPreviousStrafeTransitionAnim() const;
    UFUNCTION(BlueprintCallable, BlueprintPure)
    UAnimSequence* GetPreviousStrafeLocomotionAnim() const;
    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool ShouldPivot() const;
private:
    bool StrafeAnimationInPriorityRange(const FStrafeAnimation& StrafeAnimation, const float DirectionDegrees) const;
    bool StrafeAnimationInRange(const FStrafeAnimation& StrafeAnimation, const float DirectionDegrees) const;

};
