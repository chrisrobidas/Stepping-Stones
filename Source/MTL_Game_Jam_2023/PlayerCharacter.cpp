#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

const float MAX_SPEED = 100.0f;

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	_capsule = GetCapsuleComponent();
	_capsule->SetCapsuleHalfHeight(88.0f);
	_capsule->SetCapsuleRadius(40.0f);

	_playerCharacterMesh = GetMesh();

	_mainCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	_mainCameraArm->SetupAttachment(GetRootComponent());
	_mainCameraArm->TargetArmLength = 1000.0f;
	_mainCameraArm->bUsePawnControlRotation = false;

	_mainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	_mainCamera->SetupAttachment(_mainCameraArm, USpringArmComponent::SocketName);

	_mainCamera->bUsePawnControlRotation = false;

	JumpMaxHoldTime = 1.0f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(_playerCharacterMappingContext, 0);
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInputComponent->BindAction(_makeJumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MakeJump);
		enhancedInputComponent->BindAction(_stopJumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::StopJump);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(1.0f);
}

void APlayerCharacter::MakeJump(const FInputActionValue& Value)
{
	const bool currentValue = Value.Get<bool>();

	if (currentValue)
	{
		Jump();
	}
}

void APlayerCharacter::StopJump(const FInputActionValue& Value)
{
	const bool currentValue = Value.Get<bool>();

	if (!currentValue)
	{
		StopJumping();
	}
}

void APlayerCharacter::Move(const float Value)
{
	if (Value)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}
