#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class MTL_GAME_JAM_2023_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* _playerCharacterMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* _makeJumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* _stopJumpAction;

	void MakeJump(const FInputActionValue& Value);
	void StopJump(const FInputActionValue& Value);

	void Move(const float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* _capsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* _playerCharacterMesh;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* _mainCameraArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* _mainCamera;
};
