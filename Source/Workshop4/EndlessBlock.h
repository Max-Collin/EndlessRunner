// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndlessBlock.generated.h"

class AObstacle;
class ABlockSpawner;
class UBoxComponent;

UCLASS()
class WORKSHOP4_API AEndlessBlock : public AActor
{
	GENERATED_BODY()



	
public:	
	// Sets default values for this actor's properties
	AEndlessBlock();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
        TObjectPtr<UBoxComponent> EndCollision;

		UPROPERTY(EditAnywhere,BlueprintReadOnly)
    	TObjectPtr<UStaticMeshComponent> FloorMesh;

	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual  void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere)
		TObjectPtr<ABlockSpawner> Spawner;
		UPROPERTY(VisibleAnywhere)
    		TArray<AObstacle*> Obstacles;
    	
private:


	
	
};
