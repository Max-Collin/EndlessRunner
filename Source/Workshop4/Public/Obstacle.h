// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"


class UBoxComponent;

UCLASS()
class WORKSHOP4_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();

	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UBoxComponent> Collision;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> Mesh;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
