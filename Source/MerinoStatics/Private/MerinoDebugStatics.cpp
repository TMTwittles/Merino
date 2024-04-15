// Fill out your copyright notice in the Description page of Project Settings.


#include "MerinoDebugStatics.h"

void UMerinoDebugStatics::DrawSingleFrameDebugLine(UWorld* World, FVector Start, FVector End, FColor Color)
{
	DrawDebugLine(World, Start, End, Color, false, -1, 0, 1.0f);
}

void UMerinoDebugStatics::DrawDebugLineForDuration(UWorld* World, FVector Start, FVector End, FColor Color, float Duration)
{
	DrawDebugLine(World, Start, End, Color, false, Duration, 0, 1.0f);
}

void UMerinoDebugStatics::DrawSingleFrameDebugSphere(UWorld* World, FVector Location, float Radius, FColor Color)
{
	DrawDebugSphere(World, Location, Radius, 10, Color);
}

void UMerinoDebugStatics::DrawDebugSphereForDuration(UWorld* World, FVector Location, float Radius, FColor Color, float Duration)
{
	DrawDebugSphere(World, Location, Radius, 10, Color, false, Duration);
}
