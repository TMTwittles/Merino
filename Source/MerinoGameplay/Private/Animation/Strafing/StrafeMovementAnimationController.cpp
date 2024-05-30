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
	ActiveStrafeDirection = EStrafeDirection::NONE;
}

EStrafeDirection UStrafeMovementAnimationController::EvaluateActiveStrafeDirection(const float InSignedDirectionDegrees)
{
	if (InvalidMovementDirection(InSignedDirectionDegrees) || ActiveStrafeDirection == EStrafeDirection::NONE) return EStrafeDirection::NONE;
	bool bChangeStrafeDirection = StrafeDirectionInRange(ActiveStrafeDirection, InSignedDirectionDegrees) == false;

	if (bChangeStrafeDirection)
	{
		TArray<EStrafeDirection> Keys;
		MovementRangesMap.GetKeys(Keys);
		for (EStrafeDirection Direction : Keys)
		{
			if (bChangeStrafeDirection &&
				StrafeDirectionInRange(Direction, InSignedDirectionDegrees))
			{
				ActiveStrafeDirection = Direction;
				UE_LOG(LogTemp, Log, TEXT("Changed strafe direction %s to %f"), *UEnum::GetValueAsString(ActiveStrafeDirection), MovementRangesMap[ActiveStrafeDirection].StrafeDirectionDegrees);
				bChangeStrafeDirection = false;
			}
		}
	}

	if (bChangeStrafeDirection)
	{
		UE_LOG(LogTemplateGameplayInvalidConfig, Error, TEXT("No movement range for %f"), InSignedDirectionDegrees);
	}

	return ActiveStrafeDirection;
}

float UStrafeMovementAnimationController::GetAngleRelativeToActiveStrafeDirection(const float InMovementDirectionDegrees) const
{
	return GetAngleRelativeToStrafeDirection(ActiveStrafeDirection, InMovementDirectionDegrees);
}

float UStrafeMovementAnimationController::GetAngleRelativeToStrafeDirection(const EStrafeDirection InStrafeDirection, float InMovementDirectionDegrees) const
{
	if (MovementRangesMap.Contains(InStrafeDirection) == false)
	{
		UE_LOG(LogTemplateGameplayInvalidConfig, Error, TEXT("No entry for strafe direction %s exists."), *UEnum::GetValueAsString(InStrafeDirection));
		return -1.0f;
	}

	const FStrafeMovementRange MovementRange = MovementRangesMap[InStrafeDirection];
	if (MovementRange.StrafeDirectionDegrees == 0 || InMovementDirectionDegrees == 0)
	{
		// If the strafe direction degrees is 0, InMovementDirectionDegrees would already be relative in range 90,-90 degrees.
		return InMovementDirectionDegrees;
	}
	return MovementRange.StrafeDirectionDegrees - UMerinoMathStatics::ConvertToClockWiseRotationDegrees(InMovementDirectionDegrees);
}

float UStrafeMovementAnimationController::GetStrafeDirectionDegrees(const EStrafeDirection InStrafeDirection) const
{
	return MovementRanges[(int)InStrafeDirection].StrafeDirectionDegrees;
}

void UStrafeMovementAnimationController::ConfigureMovementRanges()
{
	/*MovementRanges.SetNum(NUM_STRAFE_DIRECTIONS);
	
	float DirectionDegrees = FORWARD_STRAFE_DIRECTION_DEGREES;
	for (int i = 0; i < NUM_STRAFE_DIRECTIONS; i++)
	{
		MovementRanges[i] = BuildStrafeMovementRange(DirectionDegrees, STRAFE_RANGE_DEGREES);
		UE_LOG(LogTemp, Log, TEXT("Constructed range %s, direction = %f, range = %f"), *UEnum::GetValueAsString((EStrafeDirection)i), DirectionDegrees, STRAFE_RANGE_DEGREES);
		DirectionDegrees += STRAFE_RANGE_DEGREES * 2;
	}*/
}

void UStrafeMovementAnimationController::SetMovementRange(const EStrafeDirection InStrafeDirection, const float InDirectionDegrees, const float InRangeDegreesLeft, const float InRangeDegreesRight)
{
	if (MovementRangesMap.Contains(InStrafeDirection))
	{
		UE_LOG(LogTemplateGameplayInvalidConfig, Error, TEXT("Movement range for strafe direction %s already exists."), *UEnum::GetValueAsString(InStrafeDirection));
		return;
	}
	MovementRangesMap.Add(InStrafeDirection, BuildStrafeMovementRange(InDirectionDegrees, InRangeDegreesLeft, InRangeDegreesRight));

	if (ActiveStrafeDirection == EStrafeDirection::NONE)
	{
		ActiveStrafeDirection = InStrafeDirection;
	}
}

FStrafeMovementRange UStrafeMovementAnimationController::BuildStrafeMovementRange(const float InStrafeDirectionDegrees, const float InRangeDegreesLeft, const float InRangeDegreesRight) const
{
	FStrafeMovementRange ConstructedRange;
	ConstructedRange.StrafeDirectionDegrees = InStrafeDirectionDegrees;
	ConstructedRange.StrafeDirectionDegreesUnwind = FMath::UnwindDegrees(InStrafeDirectionDegrees);
	ConstructedRange.StrafeRangeLeft = InRangeDegreesLeft;
	ConstructedRange.StrafeRangeRight = InRangeDegreesRight;
	return ConstructedRange;
}

bool UStrafeMovementAnimationController::StrafeDirectionInRange(const EStrafeDirection Direction, const float InSignedDirectionDegrees) const
{
	if (MovementRangesMap.Contains(Direction) == false)
	{
		UE_LOG(LogTemplateGameplayInvalidConfig, Error, TEXT("No entry for strafe direction %s exists."), *UEnum::GetValueAsString(Direction));
		return false;
	}

	float RelativeAngle = GetAngleRelativeToStrafeDirection(Direction, InSignedDirectionDegrees);
	UE_LOG(LogTemp, Log, TEXT("Direction %s Value: %f"), *UEnum::GetValueAsString(Direction), InSignedDirectionDegrees);
	FStrafeMovementRange MovementRange = MovementRangesMap[Direction];
	return UMerinoMathStatics::IsFloatInArbitraryRange(RelativeAngle, MovementRange.StrafeRangeLeft, MovementRange.StrafeRangeRight);
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