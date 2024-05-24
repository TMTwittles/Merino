// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterAimingComponent.generated.h"

class ACharacter;

/*
* 
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MERINOGAMEPLAY_API UCharacterAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AimAttributes", meta = (AllowPrivateAccess = "true"))
	float AimDurationSeconds = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AimInfo", meta = (AllowPrivateAccess="true"))
	bool bIsAiming;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AimInfo", meta = (AllowPrivateAccess="true"))
	TObjectPtr<AActor> AimTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AimInfo", meta = (AllowPrivateAccess = "true"))
	float ElapsedAimDurationSeconds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AimInfo", meta = (AllowPrivateAccess = "true"))
	float AimDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AimInfo", meta = (AllowPrivateAccess="true"))
	FVector AimDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AimInfo", meta = (AllowPrivateAccess="true"))
	FRotator AimRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ComponentDependencies", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACharacter> Character;

public:	
	// Sets default values for this component's properties
	UCharacterAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void TickCharacterAiming(float DeltaTime);

public:
	void RefreshCharacterAiming();

private:
	void UpdateAimTarget();
	void UpdateAimDirection();
	void EnterCharacterAiming();
	void ExitCharacterAiming();

public:

	/*
	* Calculates the rotation offset in degrees from the input direction to the current aim direction.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float CalculateRotationOffsetFromDirection(const FVector& InDirection, const FVector& ReferenceAxis) const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float CalculatePitchRotationOffsetDegrees() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float CalculateYawRotationOffsetDegrees() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE FVector GetAimVector() const { return AimDirection * AimDistance; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE FVector GetAimDirection() const { return AimDirection; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE bool IsAiming() const { return bIsAiming; }
};
