// Fill out your copyright notice in the Description page of Project Settings.
#include "MerinoMathStatics.h"

const float UMerinoMathStatics::FULL_ROTATION_DEGREES = 360.0f;

float UMerinoMathStatics::GetUnsignedAngleBetweenTwoVectors(const FVector A, const FVector B)
{
	return acos(FVector::DotProduct(A, B));
}

float UMerinoMathStatics::GetSignedAngleBetweenTwoVectorsRelativeToAxis(const FVector A, const FVector B, const FVector Axis)
{
	float UnsignedAngleBetweenTwoVectors = GetUnsignedAngleBetweenTwoVectors(A, B);
	FVector CrossProduct = FVector::CrossProduct(A, B);
	float Dot = FVector::DotProduct(CrossProduct, Axis);
	return FMath::Sign(Dot) * UnsignedAngleBetweenTwoVectors;
}

float UMerinoMathStatics::GetYawFromQuat(FQuat Quat)
{
	return FMath::Atan2(2.0f*(Quat.Z*Quat.W+Quat.X*Quat.Y), -1.0f + 2.0f * (Quat.W*Quat.W - Quat.X*Quat.X));
}

float UMerinoMathStatics::GetPitchFromQuat(FQuat Quat)
{
	return FMath::Asin(-2.0f*(Quat.X*Quat.Z - Quat.W*Quat.Y));
}

FQuat UMerinoMathStatics::BuildQuatEuler(float Yaw, float Pitch, float Roll)
{
	FQuat YawQuat = FQuat(FVector::UpVector, Yaw);
	FQuat PitchQuat = FQuat(FVector::RightVector, Pitch);
	FQuat RollQuat = FQuat(FVector::ForwardVector, Roll);
	return YawQuat * PitchQuat * RollQuat;
}

FVector UMerinoMathStatics::CalculateCentroid(FVector P1, FVector P2, FVector P3)
{
	return (P1 + P2 + P3) / 3;
}

float UMerinoMathStatics::ClampFloatToValues(const float InFloat, const TArray<float>& Values)
{
	float ClampedFloat = 0.0f;
	float Delta = 0.0f;
	float SmallestDelta = FLT_MAX;
	for (float ClampableValue : Values)
	{
		Delta = FMath::Abs(ClampableValue - InFloat);
		if (Delta < SmallestDelta)
		{
			SmallestDelta = Delta;
			ClampedFloat = ClampableValue;
		}
	}
	return ClampedFloat;
}

float UMerinoMathStatics::ConvertToClockWiseRotationDegrees(const float InSignedRotationDegrees)
{
	float ClockWiseRotation = InSignedRotationDegrees;
	float Sign = FMath::Sign(InSignedRotationDegrees);
	if (Sign < 0.0f)
	{
		float UnsignedRotationDegrees = FMath::Abs(InSignedRotationDegrees);
		int NumClockWiseRotations = InSignedRotationDegrees / FULL_ROTATION_DEGREES;
		NumClockWiseRotations = NumClockWiseRotations == 0 ? 1 : NumClockWiseRotations;
		ClockWiseRotation = InSignedRotationDegrees + NumClockWiseRotations * FULL_ROTATION_DEGREES;
	}
	return ClockWiseRotation;
}

bool UMerinoMathStatics::IsFloatInArbitraryRange(const float Value, const float Bound01, const float Bound02)
{
	bool bFloatInRange = false;
	if (Bound01 <= Bound02)
	{
		bFloatInRange = FMath::IsWithinInclusive(Value, Bound01, Bound02);
	}
	else if (Bound01 > Bound02)
	{
		bFloatInRange = FMath::IsWithinInclusive(Value, Bound02, Bound01);
	}
	return bFloatInRange;
}
