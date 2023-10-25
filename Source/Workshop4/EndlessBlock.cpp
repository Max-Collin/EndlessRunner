// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessBlock.h"

#include "Obstacle.h"
#include "Components/BoxComponent.h"
#include "Public/BlockSpawner.h"

// Sets default values
AEndlessBlock::AEndlessBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));

	RootComponent = FloorMesh;

	EndCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("EndCollision"));
	EndCollision->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AEndlessBlock::BeginPlay()
{
	Super::BeginPlay();

	EndCollision->OnComponentBeginOverlap.AddDynamic(this,&AEndlessBlock::OnBoxOverlap);
	EndCollision->OnComponentEndOverlap.AddDynamic(this,&AEndlessBlock::OnBoxEndOverlap);
	
}

// Called every frame
void AEndlessBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//AddActorWorldOffset(FVector(-5.f,0.f,0.f));

}

void AEndlessBlock::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("entered"));

	if(Spawner)
	{
		Spawner->SpawnFloor();
	}
	
}

void AEndlessBlock::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("exited"));

	for(int i = 0; i<Obstacles.Num();i++)
	{
		Obstacles[i]->Destroy();
	}
	
	Destroy();
}

