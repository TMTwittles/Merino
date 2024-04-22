// Fill out your copyright notice in the Description page of Project Settings.
#include "MerinoMathStatics.h"

float UMerinoMathStatics::GetUnsignedAngleBetweenTwoVectors(const FVector A, const FVector B)
{
	return acos(FVector::DotProduct(A, B));
}

float UMerinoMathStatics::GetSignedAngleBetweenTwoVectorsRelativeToAxis(const FVector A, const FVector B, const FVector Axis)
{
	float UnsignedAngleBetweenTwoVectors = GetUnsignedAngleBetweenTwoVectors(A, B);
	FVector CrossProduct = FVector::CrossProduct(A, B);
	float Dot = FVector::DotProduct(CrossProduct, Axis);
	// Set dot multiplier to either 1.0 or -1.0 based dot product of cross product.
	float DotMultiplier = Dot > 0.0f ? 1.0f : -1.0f;
	float MaxAngleDegrees = 180.0f;
	float MinAngleDegrees = -180.0f;
	float MaxAngle = FMath::DegreesToRadians(MaxAngleDegrees);
	float MinAngle = FMath::DegreesToRadians(MinAngleDegrees);
	return DotMultiplier * UnsignedAngleBetweenTwoVectors;
	return FMath::Clamp(DotMultiplier * UnsignedAngleBetweenTwoVectors, MinAngle, MaxAngle);
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
