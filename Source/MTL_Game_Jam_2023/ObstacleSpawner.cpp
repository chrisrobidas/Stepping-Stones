#include "ObstacleSpawner.h"

const double SPACE_BETWEEN_OBSTACLES = 5000.0;

AObstacleSpawner::AObstacleSpawner()
{
	_triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ObstacleSpawnerTriggerBox"));
	_triggerBox->SetupAttachment(GetRootComponent());
	_triggerBox->SetBoxExtent(FVector(200, 200, 2000), false);
	_triggerBox->SetGenerateOverlapEvents(true);
	_triggerBox->Activate();

	PrimaryActorTick.bCanEverTick = false;
}

void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
	_triggerBox->OnComponentBeginOverlap.AddDynamic(this, &AObstacleSpawner::OnOverlapBegin);

	SpawnRandomObstacle();
	SpawnRandomBackground();
	SpawnRandomProp();
	_nextObstacleX += SPACE_BETWEEN_OBSTACLES;

	SpawnRandomObstacle();
	SpawnRandomBackground();
	SpawnRandomProp();
	_nextObstacleX += SPACE_BETWEEN_OBSTACLES;

	MoveTriggerBox();
}

void AObstacleSpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("In Overlap Begin"));
	if (OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("In Overlap Begin"));
		SpawnRandomObstacle();
		SpawnRandomBackground();
		SpawnRandomProp();

		_nextObstacleX += SPACE_BETWEEN_OBSTACLES;
		MoveTriggerBox();
	}
}

void AObstacleSpawner::SpawnRandomObstacle()
{
	if (_nbOfObstaclesSpawnedForEra >= _nbOfObstaclesUntilTransition) {
		_currentEra = (_currentEra + 1) % 3;

		if (!_isFireUnlocked && _currentEra == 1)
		{
			_isFireUnlocked = true;
		}

		if (!_isShieldUnlocked && _currentEra == 2)
		{
			_isShieldUnlocked = true;
		}

		_nbOfObstaclesSpawnedForEra = 0;
	}

	FTransform spawnTransform = FTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(_nextObstacleX, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f));
	AObstacleBase* newObstacle = GetWorld()->SpawnActor<AObstacleBase>(ChooseRandomObstacleFromCurrentEra(), spawnTransform);
	_spawnedObstacles.Add(newObstacle);

	if (_spawnedObstacles.Num() > 5)
	{
		AObstacleBase* obstacleToDestroy = _spawnedObstacles[0];
		_spawnedObstacles.Remove(obstacleToDestroy);
		obstacleToDestroy->Destroy();
	}

	_nbOfObstaclesSpawnedForEra++;
}

void AObstacleSpawner::SpawnRandomBackground()
{
	FTransform spawnTransform = FTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(_nextObstacleX, -5000.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f));
	AObstacleBase* newObstacle = GetWorld()->SpawnActor<AObstacleBase>(ChooseRandomBackgroundFromCurrentEra(), spawnTransform);
	_spawnedBackgrounds.Add(newObstacle);

	if (_spawnedBackgrounds.Num() > 5)
	{
		AObstacleBase* obstacleToDestroy = _spawnedBackgrounds[0];
		_spawnedBackgrounds.Remove(obstacleToDestroy);
		obstacleToDestroy->Destroy();
	}
}

void AObstacleSpawner::SpawnRandomProp()
{
	FTransform spawnTransform = FTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(_nextObstacleX, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f));
	AObstacleBase* newObstacle = GetWorld()->SpawnActor<AObstacleBase>(ChooseRandomPropFromCurrentEra(), spawnTransform);
	_spawnedProps.Add(newObstacle);

	if (_spawnedProps.Num() > 5)
	{
		AObstacleBase* obstacleToDestroy = _spawnedProps[0];
		_spawnedProps.Remove(obstacleToDestroy);
		obstacleToDestroy->Destroy();
	}
}

void AObstacleSpawner::MoveTriggerBox()
{
	SetActorLocation(FVector(GetActorLocation().X + SPACE_BETWEEN_OBSTACLES, 0.0f, 550.0f));
}

TSubclassOf<AObstacleBase> AObstacleSpawner::ChooseRandomObstacleFromCurrentEra()
{
		int index = 0;
		switch (_currentEra)
		{
		case 0:
				index = FMath::RandRange(0, _spawnablePrehistoricObstacles.Num() - 1);
				return _spawnablePrehistoricObstacles[index];
		case 1:
				index = FMath::RandRange(0, _spawnableMiddleAgeObstacles.Num() - 1);
				return _spawnableMiddleAgeObstacles[index];
		case 2:
				index = FMath::RandRange(0, _spawnableModernObstacles.Num() - 1);
				return _spawnableModernObstacles[index];
		default:
				break;
		}
		return _spawnablePrehistoricObstacles[index];
}

TSubclassOf<AObstacleBase> AObstacleSpawner::ChooseRandomBackgroundFromCurrentEra()
{
	int index = 0;
	switch (_currentEra)
	{
	case 0:
		index = FMath::RandRange(0, _spawnablePrehistoricBackground.Num() - 1);
		return _spawnablePrehistoricBackground[index];
	case 1:
		index = FMath::RandRange(0, _spawnableMiddleAgeBackground.Num() - 1);
		return _spawnableMiddleAgeBackground[index];
	case 2:
		index = FMath::RandRange(0, _spawnableModernBackground.Num() - 1);
		return _spawnableModernBackground[index];
	default:
		break;
	}
	return _spawnablePrehistoricBackground[index];
}

TSubclassOf<AObstacleBase> AObstacleSpawner::ChooseRandomPropFromCurrentEra()
{
	int index = 0;
	switch (_currentEra)
	{
	case 0:
		index = FMath::RandRange(0, _spawnablePrehistoricProps.Num() - 1);
		return _spawnablePrehistoricProps[index];
	case 1:
		index = FMath::RandRange(0, _spawnableMiddleAgeProps.Num() - 1);
		return _spawnableMiddleAgeProps[index];
	case 2:
		index = FMath::RandRange(0, _spawnableModernProps.Num() - 1);
		return _spawnableModernProps[index];
	default:
		break;
	}
	return _spawnablePrehistoricProps[index];
}
