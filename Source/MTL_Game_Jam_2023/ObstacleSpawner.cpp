#include "ObstacleSpawner.h"

AObstacleSpawner::AObstacleSpawner()
{
	_triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ObstacleSpawnerTriggerBox"));
	_triggerBox->SetupAttachment(GetRootComponent());
	_triggerBox->SetBoxExtent(FVector(200, 200, 200), false);

	_triggerBox->OnComponentBeginOverlap.AddDynamic(this, &AObstacleSpawner::OnOverlapBegin);

	PrimaryActorTick.bCanEverTick = false;
}

void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AObstacleSpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Some warning message"));
}
