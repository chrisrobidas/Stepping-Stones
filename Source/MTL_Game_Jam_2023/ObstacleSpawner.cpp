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
	//_triggerBox->OnComponentBeginOverlap.AddDynamic(this, &AObstacleSpawner::OnOverlapBegin);

	SpawnRandomObstacle();
}

void AObstacleSpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("In Overlap Begin"));
	if (OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("In Overlap Begin"));
		SpawnRandomObstacle();
		MoveTriggerBox();
	}
}

void AObstacleSpawner::SpawnRandomObstacle()
{
	if (_nbOfObstaclesSpawnedForEra >= _nbOfObstaclesUntilTransition) {
		_currentEra %= _currentEra + 1;
	}
	FTransform spawnTransform = FTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(_nextObstacleX, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f));
	AObstacleBase* newObstacle = GetWorld()->SpawnActor<AObstacleBase>(ChooseRandomObstacleFromCurrentEra(), spawnTransform);
	_spawnedObstacles.Add(newObstacle);

	_nextObstacleX += SPACE_BETWEEN_OBSTACLES;

	if (_spawnedObstacles.Num() > 3)
	{
		AObstacleBase* obstacleToDestroy = _spawnedObstacles[0];
		_spawnedObstacles.Remove(obstacleToDestroy);
		obstacleToDestroy->Destroy();
	}
}

void AObstacleSpawner::MoveTriggerBox()
{
	SetActorLocation(FVector(GetActorLocation().X + SPACE_BETWEEN_OBSTACLES, 0.0f, 550.0f));
}

TSubclassOf<AObstacleBase> AObstacleSpawner::ChooseRandomObstacle()
{
	int index = FMath::RandRange(0, _spawnableObstacles.Num() - 1);
	return _spawnableObstacles[index];
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
		return _spawnableObstacles[index];
}
