#pragma once

#include "CameraOperationMode.generated.h"

UENUM(BlueprintType)
enum class ECameraOperationMode
{
	FreeLook UMETA(DisplayName = "Free look"),
	Aim UMETA(DisplayName = "Aim")
};
