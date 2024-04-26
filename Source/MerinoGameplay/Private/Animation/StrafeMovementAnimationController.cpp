// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/StrafeMovementAnimationController.h"
#include "MerinoGameplay.h"
#include "Animation/AnimSequence.h"
#include "Animation/BlendSpace.h"

void UStrafeMovementAnimationController::AddDirections(TArray<FStrafeAnimation> InStrafeAnimations)
{
	for (FStrafeAnimation StrafeAnim : InStrafeAnimations)
	{
		StrafeAnimations.Add(StrafeAnim);
	}
}

void UStrafeMovementAnimationController::EvaluateActiveStrafeAnimation(float InStrafeDirectionDegrees)
{
	if (InStrafeDirectionDegrees == 0.0f || 
		StrafeAnimationInRange(ActiveStrafeAnimation, InStrafeDirectionDegrees))
	{
		bShouldPivot = 0;
		return;
	}
	
	for (FStrafeAnimation StrafeAnimation : StrafeAnimations)
	{
		if (StrafeAnimationInPriorityRange(StrafeAnimation, InStrafeDirectionDegrees))
		{
			bShouldPivot = 1;
			PreviousStrafeAnimation = ActiveStrafeAnimation;
			ActiveStrafeAnimation = StrafeAnimation;
			return;
		}
	}

	UE_LOG(LogTemplateGameplayInvalidConfig, Error, TEXT("Unable to evaluate strafe animation for degrees %f"), InStrafeDirectionDegrees);
}

UAnimSequence* UStrafeMovementAnimationController::GetActiveStrafeTransitionAnim() const
{
	return ActiveStrafeAnimation.TransitionAnim;
}

UAnimSequence* UStrafeMovementAnimationController::GetActiveStrafeLocomotionAnim() const
{
	return ActiveStrafeAnimation.LocomotionAnim;
}

UBlendSpace* UStrafeMovementAnimationController::GetActiveStrafeBlendSpace() const
{
	return ActiveStrafeAnimation.StrafeMovementBS;
}

UAnimSequence* UStrafeMovementAnimationController::GetPreviousStrafeTransitionAnim() const
{
	return PreviousStrafeAnimation.TransitionAnim;
}

UAnimSequence* UStrafeMovementAnimationController::GetPreviousStrafeLocomotionAnim() const
{
	return PreviousStrafeAnimation.LocomotionAnim;
}

bool UStrafeMovementAnimationController::ShouldPivot() const
{
	return bShouldPivot == 1;
}

bool UStrafeMovementAnimationController::StrafeAnimationInPriorityRange(const FStrafeAnimation& StrafeAnimation, const float DirectionDegrees) const
{
	return (DirectionDegrees >= StrafeAnimation.PriorityMinDegrees &&
		DirectionDegrees <= StrafeAnimation.PriorityMaxDegrees);
}

bool UStrafeMovementAnimationController::StrafeAnimationInRange(const FStrafeAnimation& StrafeAnimation, const float DirectionDegrees) const
{
	float MinDegrees = StrafeAnimation.PriorityMinDegrees * 1.25;
	MinDegrees = FMath::Clamp(MinDegrees, -180.0f, 180.0f);
	float MaxDegrees = StrafeAnimation.PriorityMaxDegrees * 1.25;
	MaxDegrees = FMath::Clamp(MaxDegrees, -180.0f, 180.0f);
	return (DirectionDegrees >= MinDegrees &&
		DirectionDegrees <= MaxDegrees);
}

