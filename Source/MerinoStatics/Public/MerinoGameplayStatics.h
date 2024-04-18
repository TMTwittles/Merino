// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MerinoGameplayStatics.generated.h"

/**
 * 
 */
UCLASS()
class MERINOSTATICS_API UMerinoGameplayStatics : public UObject
{
	GENERATED_BODY()

public:
	bool CheckActorGrounded(UWorld* World, AActor* Actor);
	static float CalculateDecelerationTime(FVector* PrevVelocity, FVector* CurrentVelocity, float Deceleration);
};
