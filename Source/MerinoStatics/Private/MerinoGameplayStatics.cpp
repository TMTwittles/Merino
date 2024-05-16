// Fill out your copyright notice in the Description page of Project Settings.

#include "MerinoGameplayStatics.h"
#include "MerinoMathStatics.h"
#include "MerinoStatics.h"

void UMerinoGameplayStatics::SetControlRotationToDirection(AController* Controller, const FVector& Direction)
{
	if (Controller == nullptr)
	{
		UE_LOG(LogTemplateStaticsInvalidConfig, Error, TEXT("Controller is null, ensure valid controller."));
		return;
	}
	
	const FRotator ControlRotation = Controller->GetControlRotation();
	const FVector UpDirection = FRotationMatrix(ControlRotation).GetUnitAxis(EAxis::Z);
	const float YawRotationAmount = UMerinoMathStatics::GetSignedAngleBetweenTwoVectorsRelativeToAxis(
		FVector::ForwardVector.GetSafeNormal(),
		Direction,
		UpDirection);
	Controller->SetControlRotation(FRotator(0.0f, FMath::RadiansToDegrees(YawRotationAmount), 0.0f));
}

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
