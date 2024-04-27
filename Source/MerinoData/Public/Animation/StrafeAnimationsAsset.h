// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Animation/AnimSequence.h"
#include "Animation/BlendSpace.h"
#include "StrafeAnimationsAsset.generated.h"

/**
 * Data asset houses animation references when strafing. 
 */
UCLASS(Blueprintable)
class MERINODATA_API UStrafeAnimationsAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=EnterStrafeAnimation)
	TObjectPtr<UAnimSequence> EnterStrafeAnimSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StrafeLocomotion)
	TObjectPtr<UBlendSpace> StrafeLocomotionBS;
};
