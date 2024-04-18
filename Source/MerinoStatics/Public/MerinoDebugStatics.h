// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MerinoDebugStatics.generated.h"

/**
 * 
 */
UCLASS()
class MERINOSTATICS_API UMerinoDebugStatics : public UObject
{
	GENERATED_BODY()

public:
	static void DrawSingleFrameDebugLine(UWorld* World, FVector Start, FVector End, FColor Color);
	static void DrawDebugLineForDuration(UWorld* World, FVector Start, FVector End, FColor Color, float Duration);
	static void DrawSingleFrameDebugSphere(UWorld* World, FVector Location, float Radius, FColor Color);
	static void DrawDebugSphereForDuration(UWorld* World, FVector Location, float Radius, FColor Color, float Duration);
};
