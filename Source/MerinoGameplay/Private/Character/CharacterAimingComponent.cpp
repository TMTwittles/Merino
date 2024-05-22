// Fill out your copyright notice in the Description page of Project Settings.
#include "Character/CharacterAimingComponent.h"
#include "MerinoDebugStatics.h"
#include "MerinoGameplayStatics.h"
#include "MerinoMathStatics.h"
#include "MerinoGameplay.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCharacterAimingComponent::UCharacterAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
	AimTarget == nullptr;
	ElapsedAimDurationSeconds = 0.0f;
}

// Called when the game starts
void UCharacterAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	AimDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	Character = Cast<ACharacter>(GetOwner());
	if (Character == nullptr)
	{
		UE_LOG(LogTemplateGameplayInvalidConfig, Error, TEXT("Character aiming component attached to actor %s that is not a character"), *GetOwner()->GetName());
		return;
	}
}

// Called every frame
void UCharacterAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsAiming && Character != nullptr)
	{
		UMerinoDebugStatics::DrawSingleFrameDebugLine(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector().GetSafeNormal() * 1000.0f, FColor::Red);
		TickCharacterAiming(DeltaTime);
	}
}

void UCharacterAimingComponent::TickCharacterAiming(float DeltaTime)
{
	if (ElapsedAimDurationSeconds <= 0.0f)
	{
		ExitCharacterAiming();
		return;
	}

	ElapsedAimDurationSeconds -= DeltaTime;
	UpdateAimDirection();
	UMerinoGameplayStatics::SetControlRotationToDirection(Character->GetController(), AimDirection);
}

void UCharacterAimingComponent::RefreshCharacterAiming()
{
	EnterCharacterAiming();
	UpdateAimTarget();
	UpdateAimDirection();
}

void UCharacterAimingComponent::UpdateAimTarget()
{
	AActor* BestAimTarget = nullptr;
	TArray<AActor*> AimableActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Attackable"), AimableActors);

	FVector ActorLocation = GetOwner()->GetActorLocation();
	float BestDistance = FLT_MAX;
	float CurrDistance = 0.0f;
	float BestDot = -1.0f;
	float CurrDot = -1.0f;
	// TODO: Factor DOT product into calculations.
	for (AActor* AimableActor : AimableActors)
	{
		CurrDistance = FVector::Distance(ActorLocation, AimableActor->GetActorLocation());
		CurrDot = FVector::DotProduct(ActorLocation, AimableActor->GetActorLocation());
		if (CurrDistance < BestDistance)
		{
			BestDistance = CurrDistance;
			BestAimTarget = AimableActor;
		}
	}
	AimTarget = BestAimTarget;
}

void UCharacterAimingComponent::UpdateAimDirection()
{
	AimDirection = AimTarget != nullptr ?
		(AimTarget->GetActorLocation() - GetOwner()->GetActorLocation()).GetSafeNormal() :
		GetOwner()->GetActorForwardVector().GetSafeNormal();
}

void UCharacterAimingComponent::EnterCharacterAiming()
{
	bIsAiming = true;
	ElapsedAimDurationSeconds = AimDurationSeconds;
	Character->GetCharacterMovement()->bOrientRotationToMovement = false;
	Character->GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

void UCharacterAimingComponent::ExitCharacterAiming()
{
	bIsAiming = false;
	ElapsedAimDurationSeconds = 0.0f;
	Character->GetCharacterMovement()->bOrientRotationToMovement = true;
	Character->GetCharacterMovement()->bUseControllerDesiredRotation = false;
}

float UCharacterAimingComponent::CalculateRotationOffsetFromDirection(const FVector& InDirection, const FVector& ReferenceAxis) const
{
	float offset = UMerinoMathStatics::GetSignedAngleBetweenTwoVectorsRelativeToAxis(InDirection, AimDirection, ReferenceAxis);
	FVector StartLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector().GetSafeNormal() * 100;
	return FMath::RadiansToDegrees(offset);
}

