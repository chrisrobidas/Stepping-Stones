#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ObstacleSpawner.generated.h"

UCLASS()
class MTL_GAME_JAM_2023_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	AObstacleSpawner();

protected:
	virtual void BeginPlay() override;

private:
	float _nextObstacleX;
	float _nextObstacleZ;

	UBoxComponent* _triggerBox;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
