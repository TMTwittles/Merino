// Copyright Epic Games, Inc. All Rights Reserved.

#include "MerinoCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MerinoGameplay/Public/Camera/CharacterCameraOperatorComponent.h"
#include "MerinoGameplay/Public/Character/CharacterAimingComponent.h"
#include "Math/UnrealMathUtility.h"
#include "MerinoDebugStatics.h"
#include "MerinoMathStatics.h"
#include "AbilitySystemComponent.h"
#include "StandardAttributeSet.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AMerinoCharacter

AMerinoCharacter::AMerinoCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Configure character movement
	// Character rotates in direction of control rotation when shooting or firing.
	GetCharacterMovement()->bUseControllerDesiredRotation = false; 
	// Character moves in direction of input when they are not shooting or aiming.
	GetCharacterMovement()->bOrientRotationToMovement = true; 	
	// TODO: Might want to look into changing the rotation rate when aiming and shooting.
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AttributeSet = CreateDefaultSubobject<UStandardAttributeSet>(TEXT("StandardAttributeSet"));

	// Create a CharacterCameraOperator, this operates the camera dynamically.
	// Starting mode is free look. 
	CameraOperatorComp = CreateDefaultSubobject<UCharacterCameraOperatorComponent>(TEXT("CameraOperator"));

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation

	// By default character is not shooting.
	bIsShooting = 0;

	// By default character is not aiming. 
	bIsAiming = 0;
	CharacterAimingComp = CreateDefaultSubobject<UCharacterAimingComponent>(TEXT("CharacterAiming"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

UAbilitySystemComponent* AMerinoCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}

void AMerinoCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Grant abilities to the character.
	GrantAbilities();

	// Set camera opertion mode.
	CameraOperatorComp->SetCameraOperationMode(ECameraOperationMode::FreeLook);

	// Spawn weapon
	SpawnWeapon();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input
void AMerinoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMerinoCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMerinoCharacter::Look);

		// Start and exit aiming
		EnhancedInputComponent->BindAction(AimingAction, ETriggerEvent::Started, this, &AMerinoCharacter::EnterAim);
		EnhancedInputComponent->BindAction(AimingAction, ETriggerEvent::Completed, this, &AMerinoCharacter::ExitAim);

		// Start and stop shooting.
		EnhancedInputComponent->BindAction(ShootingAction, ETriggerEvent::Started, this, &AMerinoCharacter::StartShooting);
		EnhancedInputComponent->BindAction(ShootingAction, ETriggerEvent::Completed, this, &AMerinoCharacter::ExitShooting);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMerinoCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// find out which way is forward
	const FRotator Rotation = CameraOperatorComp->GetCurrentCameraRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement 
	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AMerinoCharacter::Look(const FInputActionValue& Value)
{
	// Input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		//AddControllerYawInput(LookAxisVector.X);
		//AddControllerPitchInput(LookAxisVector.Y);
		CameraOperatorComp->AddYaw(LookAxisVector.X);
		CameraOperatorComp->AddPitch(LookAxisVector.Y);
	}
}

void AMerinoCharacter::GrantAbilities()
{
	for (TSubclassOf<UGameplayAbility> Ability : GameplayAbilities)
	{
		FGameplayAbilitySpec AbilitySpec(
			Ability,
			0,
			0
		);
		AbilitySystem->GiveAbility(AbilitySpec);
	}
}

void AMerinoCharacter::EnterAim(const FInputActionValue& Value)
{
	bIsAiming = 1;
	EnterAimingOrShooting();
}

void AMerinoCharacter::ExitAim(const FInputActionValue& Value)
{
	bIsAiming = 0;
	ExitAimingOrShooting();
}

void AMerinoCharacter::StartShooting(const FInputActionValue& Value)
{
	bIsShooting = 1;
	CharacterAimingComp->RefreshCharacterAiming();
	AbilitySystem->AbilityLocalInputPressed(0);
	EnterAimingOrShooting();
}

void AMerinoCharacter::ExitShooting(const FInputActionValue& Value)
{
	bIsShooting = 0;
	ExitAimingOrShooting();
}

// Note, we still aim when firing our weapon, this can be considered hip fire. Moving this logic
// into a state machine will make this less edge casey and confusing. 
void AMerinoCharacter::Aim(const FInputActionValue& Value)
{
	// TODO: Implement
}

void AMerinoCharacter::EnterAimingOrShooting()
{
	// TODO: Implement	
}

void AMerinoCharacter::ExitAimingOrShooting()
{
	// TODO: Implement
}

void AMerinoCharacter::SpawnWeapon()
{
	if (WeaponType == nullptr)
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("Unable to spawn weapon due to invalid weapon type."));
		return;
	}

	if (GetMesh()->DoesSocketExist(WeaponAttachmentSocket) == false)
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("Unable to spawn weapon with socket name %s, unable to locate socket on the character mesh."), WeaponAttachmentSocket);
		return;
	}

	FActorSpawnParameters WeaponSpawnParameters;
	WeaponSpawnParameters.Owner = this; 
	WeaponSpawnParameters.Instigator = this; 

	EquipedWeapon = GetWorld()->SpawnActor<AEquipableWeapon>(WeaponType, WeaponSpawnParameters);
	EquipedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponAttachmentSocket);
	EquipedWeapon->ConfigureWeaponPostAttachment();
}

bool AMerinoCharacter::IsAiming() const
{
	return bIsAiming == 1;
}

bool AMerinoCharacter::IsFiring() const
{
	return bIsShooting == 1;
}

AEquipableWeapon* AMerinoCharacter::GetEquippedWeapon() const
{
	return EquipedWeapon;
}
