// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockSpawner.generated.h"

class AObstacle;
class AEndlessBlock;

UCLASS()
 class  WORKSHOP4_API ABlockSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlockSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<AObstacle>> Obstacle;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<AEndlessBlock> EndlessBlock;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FTransform spawnPos;
	UFUNCTION()
		void  SpawnFloor();


private:



	
	UPROPERTY(VisibleAnywhere)
	float NumberofFloors = 0;
};
