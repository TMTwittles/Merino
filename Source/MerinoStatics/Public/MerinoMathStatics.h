// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "MerinoMathStatics.generated.h"

UCLASS(BlueprintType)
class MERINOSTATICS_API UMerinoMathStatics : public UObject
{
	GENERATED_BODY()

public:
	static const float FULL_ROTATION_DEGREES;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetUnsignedAngleBetweenTwoVectors(const FVector A, const FVector B);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetSignedAngleBetweenTwoVectorsRelativeToAxis(const FVector A, const FVector B, const FVector Axis);
	static float GetYawFromQuat(FQuat Quat);
	static float GetPitchFromQuat(FQuat Quat);
	static FQuat BuildQuatEuler(float Yaw, float Pitch, float Roll);
	static FVector CalculateCentroid(FVector P1, FVector P2, FVector P3);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float ClampFloatToValues(const float InFloat, const TArray<float>& Values);
	static float ConvertToClockWiseRotationDegrees(const float InSignedRotationDegrees);
	// Determines if float is within the range of 2 floats, however, no need to define which float is lower or upper bound.
	// Only use this method when unable to determine lower and upper bounds. 
	static bool IsFloatInArbitraryRange(const float Value, const float Bound01, const float Bound02);
};
