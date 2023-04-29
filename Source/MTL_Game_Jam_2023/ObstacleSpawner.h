#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ObstacleBase.h"
#include "PlayerCharacter.h"
#include "ObstacleSpawner.generated.h"

UCLASS()
class MTL_GAME_JAM_2023_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()
	
public:
	AObstacleSpawner();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AObstacleBase>> _spawnableObstacles;

private:
	double _nextObstacleX;
	double _nextObstacleZ;

	UBoxComponent* _triggerBox;

	TArray<AObstacleBase*> _spawnedObstacles;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SpawnRandomObstacle();

	UFUNCTION()
	void MoveTriggerBox();

	UFUNCTION()
	TSubclassOf<AObstacleBase> ChooseRandomObstacle();
};
