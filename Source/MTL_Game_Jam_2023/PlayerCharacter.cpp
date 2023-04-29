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

	Capsule = GetCapsuleComponent();
	Capsule->SetCapsuleHalfHeight(88.0f);
	Capsule->SetCapsuleRadius(40.0f);

	PlayerCharacterMesh = GetMesh();

	MainCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	MainCameraArm->SetupAttachment(GetRootComponent());
	MainCameraArm->TargetArmLength = 1000.0f;
	MainCameraArm->bUsePawnControlRotation = false;

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamera->SetupAttachment(MainCameraArm, USpringArmComponent::SocketName);

	MainCamera->bUsePawnControlRotation = false;

	JumpMaxHoldTime = 1.0f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerCharacterMappingContext, 0);
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MakeJumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MakeJump);
		EnhancedInputComponent->BindAction(StopJumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::StopJump);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(1.0f);
}

void APlayerCharacter::MakeJump(const FInputActionValue& Value)
{
	const bool CurrentValue = Value.Get<bool>();

	if (CurrentValue)
	{
		UE_LOG(LogTemp, Warning, TEXT("Jump"));
		Jump();
	}
}

void APlayerCharacter::StopJump(const FInputActionValue& Value)
{
	const bool CurrentValue = Value.Get<bool>();

	if (!CurrentValue)
	{
		UE_LOG(LogTemp, Warning, TEXT("Stop Jump"));
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
