// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockSpawner.h"

#include "Workshop4/EndlessBlock.h"
#include "Workshop4/Public/Obstacle.h"


// Sets default values
  ABlockSpawner::ABlockSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

  	
}

// Called when the game starts or when spawned
void ABlockSpawner::BeginPlay()
{
	Super::BeginPlay();

	for(int i = 0;i<5;i++)
	{
		SpawnFloor();
	}
  	
	
}

// Called every frame
void ABlockSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlockSpawner::SpawnFloor()
{
	
  	TObjectPtr<AEndlessBlock> Temp;
  	TObjectPtr<AObstacle> ObstacleTemp;
  	FActorSpawnParameters spawnParameters;
  	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	if(EndlessBlock)
	{
		spawnPos.SetLocation(FVector3d(NumberofFloors* 1600,0,0));
		Temp = (AEndlessBlock*)	GetWorld()->SpawnActor<AActor>(EndlessBlock, spawnPos, spawnParameters);
		  	Temp->Spawner = this;
		if(Obstacle[0]&&NumberofFloors>5)
		{
			int SpawnY;
			int rnd = rand()%3;
			switch (rnd)
			{
				case 0:
					SpawnY = 200;
					break;
				case 1:
					SpawnY = 400;
					break;
				case 2:
					SpawnY = 600;
					break;
				default:
					SpawnY = 400;
					break;
			}
			spawnPos.SetLocation((FVector3d(NumberofFloors* 1600+800,SpawnY,0)));
			ObstacleTemp = (AObstacle*)	GetWorld()->SpawnActor<AActor>(Obstacle[rand()%Obstacle.Num()],spawnPos,spawnParameters);

			Temp->Obstacles.Add(ObstacleTemp);
		}
			NumberofFloors ++;
	}
  	



  	
  
}

