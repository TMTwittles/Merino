// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "MerinoMathStatics.generated.h"

UCLASS(BlueprintType)
class MERINOSTATICS_API UMerinoMathStatics : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetUnsignedAngleBetweenTwoVectors(const FVector A, const FVector B);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetSignedAngleBetweenTwoVectorsRelativeToAxis(const FVector A, const FVector B, const FVector Axis);
	static float GetYawFromQuat(FQuat Quat);
	static float GetPitchFromQuat(FQuat Quat);
	static FQuat BuildQuatEuler(float Yaw, float Pitch, float Roll);
	static FVector CalculateCentroid(FVector P1, FVector P2, FVector P3);
};
