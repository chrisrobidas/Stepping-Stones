// Fill out your copyright notice in the Description page of Project Settings.


#include "Bush.h"
#include "Torch_Weapon.h"

// Sets default values
ABush::ABush()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABush::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABush::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_isBurning) {
			if (_timeSinceStartOfBurning >= _burningDuration) {
					SetActorHiddenInGame(true);
					SetActorTickEnabled(false);
			}
			_timeSinceStartOfBurning += DeltaTime;
	}
}

void ABush::Burn()
{
		_hurtbox->Deactivate();
		SetActorEnableCollision(false);
		_isBurning = true;
		// Begin burning animation
}

void ABush::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
		if (OtherComp->GetAttachParent()->IsA<UTorch_Weapon>()) {
				this->Burn();
		}
}

void ABush::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
