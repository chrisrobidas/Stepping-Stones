// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Components/BoxComponent.h>
#include "Torch.h"
#include "Torch_Weapon.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MTL_GAME_JAM_2023_API UTorch_Weapon : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTorch_Weapon();

	UFUNCTION(BlueprintCallable)
			void Brandish();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
			class UBoxComponent* _hitbox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
			TSubclassOf<ATorch> _torchModel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Torch parameters")
			float _attackDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Torch parameters")
			float _timeSinceStartOfBrandish = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Torch parameters")
			bool _isBrandishing = false;

	ATorch* _spawnedTorch;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

		
};
