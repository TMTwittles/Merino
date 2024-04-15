// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "MerinoMathStatics.generated.h"

UCLASS()
class MERINOSTATICS_API UMerinoMathStatics : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static float GetUnsignedAngleBetweenTwoVectors(FVector A, FVector B);
	UFUNCTION(BlueprintCallable)
	static float GetSignedAngleBetweenTwoVectorsRelativeToAxis(FVector A, FVector B, FVector Axis);
	static float GetYawFromQuat(FQuat Quat);
	static float GetPitchFromQuat(FQuat Quat);
	static FQuat BuildQuatEuler(float Yaw, float Pitch, float Roll);
	static FVector CalculateCentroid(FVector P1, FVector P2, FVector P3);
};
