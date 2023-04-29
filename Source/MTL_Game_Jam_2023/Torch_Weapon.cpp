// Fill out your copyright notice in the Description page of Project Settings.


#include "Torch_Weapon.h"
#include <Input/Events.h>
#include <string>

// Sets default values for this component's properties
UTorch_Weapon::UTorch_Weapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	_hitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	_hitbox->SetCollisionProfileName("Trigger");
	_hitbox->Deactivate();
	_hitbox->AddRelativeLocation(FVector::ForwardVector * 20.f);

	// ...
}

// Called when the game starts
void UTorch_Weapon::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	_spawnedTorch = GetWorld()->SpawnActor<ATorch>(_torchModel, FVector::ForwardVector * 20.f, FRotator::ZeroRotator, spawnParams);
	UE_LOG(LogTemp, Warning, TEXT("Spawned torch pointer : " + _spawnedTorch));
	//_spawnedTorch->SetActorHiddenInGame(true);
}


// Called every frame
void UTorch_Weapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (_isBrandishing) {
			if (_timeSinceStartOfBrandish >= _attackDuration) {
					_hitbox->Deactivate();
					_timeSinceStartOfBrandish = 0.0f;
					_spawnedTorch->SetActorHiddenInGame(true);
					_isBrandishing = false;

					// Stop brandishing animation
			}
			_timeSinceStartOfBrandish += DeltaTime;
	}
}

void UTorch_Weapon::Brandish()
{
		_isBrandishing = true;
		_hitbox->Activate();
		_spawnedTorch->SetActorHiddenInGame(false);
		// Begin brandishing animation
}

