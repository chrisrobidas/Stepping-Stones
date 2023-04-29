// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "Bush.generated.h"

UCLASS()
class MTL_GAME_JAM_2023_API ABush : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABush();

	UFUNCTION()
			void Burn();

	UFUNCTION()
			void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
			void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
			class UBoxComponent* _hurtbox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Burning")
			float _burningDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
			float _timeSinceStartOfBurning = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
			bool _isBurning = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
