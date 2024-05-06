#pragma once

#include "CameraOperationMode.generated.h"

UENUM(BlueprintType)
enum class ECameraOperationMode : uint8
{
	FreeLook UMETA(DisplayName = "Free look"),
	Aim UMETA(DisplayName = "Aim"),
	HipFire UMETA(DisplayName = "Hip fire")
};
