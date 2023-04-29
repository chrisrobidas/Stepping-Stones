#include "ObstacleBase.h"

AObstacleBase::AObstacleBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AObstacleBase::BeginPlay()
{
	Super::BeginPlay();
}
