// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/Strafing/StrafeMovementAnimationController.h"
#include "MerinoGameplay.h"
#include "Animation/AnimSequence.h"
#include "Animation/BlendSpace.h"
#include "MerinoMathStatics.h"

static const float NUM_STRAFE_DIRECTIONS = 4;
static const float FORWARD_STRAFE_DIRECTION_DEGREES = 0.0f;
static const float STRAFE_RANGE_DEGREES = 45.0f;
static const float DEGREES_POS_LIMIT = 180.0f;
static const float DEGREES_NEG_LIMIT = -180.0f;

UStrafeMovementAnimationController::UStrafeMovementAnimationController()
{
	ActiveStrafeDirection = (int) EStrafeDirection::FORWARD;
	ConfigureMovementRanges();
}

EStrafeDirection UStrafeMovementAnimationController::EvaluateActiveStrafeDirection(const float InSignedDirectionDegrees)
{
	if (InvalidMovementDirection(InSignedDirectionDegrees)) return EStrafeDirection::FORWARD;

	bool bChangeStrafeDirection = StrafeDirectionInRange(ActiveStrafeDirection, InSignedDirectionDegrees) == false;
	for (int directionIndex = 0; directionIndex < NUM_STRAFE_DIRECTIONS; directionIndex++)
	{
		if (bChangeStrafeDirection && 
			StrafeDirectionInRange(directionIndex, InSignedDirectionDegrees))
		{
			ActiveStrafeDirection = directionIndex;
			UE_LOG(LogTemp, Log, TEXT("Changed strafe direction %s to %f"), 
				*UEnum::GetValueAsString((EStrafeDirection)ActiveStrafeDirection), 
				MovementRanges[ActiveStrafeDirection].StrafeDirectionDegrees);
			bChangeStrafeDirection = false;
		}
	}
	return (EStrafeDirection) ActiveStrafeDirection;
}

float UStrafeMovementAnimationController::GetAngleRelativeToActiveStrafeDirection(const float InMovementDirectionDegrees) const
{
	if (InvalidMovementDirection(InMovementDirectionDegrees)) return -1.0f;
	
	float AngleRelativeToActiveStrafeDirection = -1.0f;
	const FStrafeMovementRange MovementRange = MovementRanges[ActiveStrafeDirection];

	// Calculate difference, use strafe direction in range -180.0f to 180.0f to determine difference. 
	const float StrafeDirectionUnwind = MovementRange.StrafeDirectionDegreesUnwind;
	const float ReferenceAngleDegrees = FMath::Abs(StrafeDirectionUnwind);
	const float InputAngleDegrees = FMath::Abs(InMovementDirectionDegrees);
	const float Difference = FMath::Abs(StrafeDirectionUnwind - InputAngleDegrees);

	// Calculate direction, i.e veering negative or positive degrees. 
	const float DirectionModifier = InMovementDirectionDegrees < StrafeDirectionUnwind ? -1.0f : 1.0f;

	AngleRelativeToActiveStrafeDirection = Difference * DirectionModifier;
	if (Difference != 0.0f)
	{
		UE_LOG(LogTemp, Log, TEXT("Difference %f"), AngleRelativeToActiveStrafeDirection);
	}
	
	return AngleRelativeToActiveStrafeDirection;
}

float UStrafeMovementAnimationController::GetStrafeDirectionDegrees(const EStrafeDirection InStrafeDirection) const
{
	return MovementRanges[(int)InStrafeDirection].StrafeDirectionDegrees;
}

void UStrafeMovementAnimationController::ConfigureMovementRanges()
{
	MovementRanges.SetNum(NUM_STRAFE_DIRECTIONS);
	
	float DirectionDegrees = FORWARD_STRAFE_DIRECTION_DEGREES;
	for (int i = 0; i < NUM_STRAFE_DIRECTIONS; i++)
	{
		MovementRanges[i] = BuildStrafeMovementRange(DirectionDegrees, STRAFE_RANGE_DEGREES);
		UE_LOG(LogTemp, Log, TEXT("Constructed range %s, direction = %f, range = %f"), *UEnum::GetValueAsString((EStrafeDirection)i), DirectionDegrees, STRAFE_RANGE_DEGREES);
		DirectionDegrees += STRAFE_RANGE_DEGREES * 2;
	}
}

FStrafeMovementRange UStrafeMovementAnimationController::BuildStrafeMovementRange(const float InStrafeDirectionDegrees, const float InStrafeRangeDegrees) const
{
	FStrafeMovementRange ConstructedRange;
	ConstructedRange.StrafeDirectionDegrees = InStrafeDirectionDegrees;
	ConstructedRange.StrafeDirectionDegreesUnwind = FMath::UnwindDegrees(InStrafeDirectionDegrees);
	ConstructedRange.StrafeRangeDegrees = InStrafeRangeDegrees;
	return ConstructedRange;
}

bool UStrafeMovementAnimationController::StrafeDirectionInRange(const int InStrafeDirection, const float InSignedDirectionDegrees) const
{
	bool bStrafeDirectionInRange = false;
	FStrafeMovementRange MovementRange = MovementRanges[InStrafeDirection];
	// To determine strafe movement we test two ranges, strafe direction - strafe range, strafe direction + strafe range.
	const int NumRanges = 2;
	float RangeStart = MovementRange.StrafeDirectionDegrees - MovementRange.StrafeRangeDegrees;
	// To determine strafe movement range all calculations are clockwise.
	const float ClockWiseDirection = UMerinoMathStatics::ConvertToClockWiseRotationDegrees(InSignedDirectionDegrees);
	float ClockWiseRangeDegrees = UMerinoMathStatics::ConvertToClockWiseRotationDegrees(RangeStart);
	for (int i = 0; i < NumRanges; i++)
	{
		bStrafeDirectionInRange = bStrafeDirectionInRange ||
			UMerinoMathStatics::IsFloatInArbitraryRange(ClockWiseDirection, ClockWiseRangeDegrees, ClockWiseRangeDegrees + MovementRange.StrafeRangeDegrees);
		ClockWiseRangeDegrees = MovementRange.StrafeDirectionDegrees;
	}
	return bStrafeDirectionInRange;
}

bool UStrafeMovementAnimationController::InvalidMovementDirection(const float InMovementDirectionDegrees) const
{
	if (InMovementDirectionDegrees > DEGREES_POS_LIMIT || InMovementDirectionDegrees < DEGREES_NEG_LIMIT)
	{
		UE_LOG(LogTemplateGameplayInvalidConfig, Error, TEXT("Input direction: %f does not fit in limits: %f and %f"), InMovementDirectionDegrees, DEGREES_POS_LIMIT, DEGREES_NEG_LIMIT);
		return true;
	}
	return false;
}