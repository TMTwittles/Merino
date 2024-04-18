// Fill out your copyright notice in the Description page of Project Settings.


#include "MerinoGameplayStatics.h"

bool UMerinoGameplayStatics::CheckActorGrounded(UWorld* World, AActor* Actor)
{
	return false;
}

float UMerinoGameplayStatics::CalculateDecelerationTime(FVector* PrevVelocity, FVector* CurrentVelocity, float Deceleration)
{
	float TotalDecelerationTime = PrevVelocity->Size() / Deceleration;
	float ElapsedDecelerationTime = (CurrentVelocity->Size() - Deceleration) / TotalDecelerationTime;
	ElapsedDecelerationTime = TotalDecelerationTime - ElapsedDecelerationTime;
	return ElapsedDecelerationTime / TotalDecelerationTime;
}
