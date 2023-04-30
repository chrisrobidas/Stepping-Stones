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
	TArray<TSubclassOf<AObstacleBase>> _spawnablePrehistoricObstacles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AObstacleBase>> _spawnableMiddleAgeObstacles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AObstacleBase>> _spawnableModernObstacles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AObstacleBase>> _spawnablePrehistoricBackground;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AObstacleBase>> _spawnableMiddleAgeBackground;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AObstacleBase>> _spawnableModernBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AObstacleBase>> _spawnablePrehistoricProps;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AObstacleBase>> _spawnableMiddleAgeProps;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AObstacleBase>> _spawnableModernProps;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool _isFireUnlocked;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool _isShieldUnlocked;

	int _currentEra = 0;
	int _nbOfObstaclesSpawnedForEra = 0;
	int _nbOfObstaclesUntilTransition = 6;

private:
	double _nextObstacleX;
	double _nextObstacleZ;

	UPROPERTY(EditAnywhere)
	UBoxComponent* _triggerBox;

	TArray<AObstacleBase*> _spawnedObstacles;
	TArray<AObstacleBase*> _spawnedBackgrounds;
	TArray<AObstacleBase*> _spawnedProps;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SpawnRandomObstacle();

	UFUNCTION()
	void SpawnRandomBackground();

	UFUNCTION()
	void SpawnRandomProp();

	UFUNCTION()
	void MoveTriggerBox();

	UFUNCTION()
	TSubclassOf<AObstacleBase> ChooseRandomObstacleFromCurrentEra();

	UFUNCTION()
	TSubclassOf<AObstacleBase> ChooseRandomBackgroundFromCurrentEra();

	UFUNCTION()
	TSubclassOf<AObstacleBase> ChooseRandomPropFromCurrentEra();
};
