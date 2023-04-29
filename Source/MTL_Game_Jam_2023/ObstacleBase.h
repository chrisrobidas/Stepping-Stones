#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleBase.generated.h"

UCLASS()
class MTL_GAME_JAM_2023_API AObstacleBase : public AActor
{
	GENERATED_BODY()
	
public:
	AObstacleBase();

protected:
	virtual void BeginPlay() override;
};
