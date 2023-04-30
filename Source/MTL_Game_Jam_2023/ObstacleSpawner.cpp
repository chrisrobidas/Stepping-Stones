#include "ObstacleSpawner.h"

const double SPACE_BETWEEN_OBSTACLES = 5000.0;

AObstacleSpawner::AObstacleSpawner()
{
	_triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ObstacleSpawnerTriggerBox"));
	_triggerBox->SetupAttachment(GetRootComponent());
	_triggerBox->SetBoxExtent(FVector(200, 200, 2000), false);
	_triggerBox->SetGenerateOverlapEvents(true);

	PrimaryActorTick.bCanEverTick = false;
}

void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
	_triggerBox->OnComponentBeginOverlap.AddDynamic(this, &AObstacleSpawner::OnOverlapBegin);

	SpawnRandomObstacle();
}

void AObstacleSpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->IsChildOf(APlayerCharacter::StaticClass()))
	{
		SpawnRandomObstacle();
		MoveTriggerBox();
	}
}

void AObstacleSpawner::SpawnRandomObstacle()
{
	FTransform spawnTransform = FTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(_nextObstacleX, 0.0f, 0.0f), FVector(1.0f, 1.0f, 1.0f));
	AObstacleBase* newObstacle = GetWorld()->SpawnActor<AObstacleBase>(ChooseRandomObstacle(), spawnTransform);
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
