// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "Components/BoxComponent.h"
#include "Workshop4/Workshop4Character.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;

	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(GetRootComponent());
	
}

void AObstacle::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TObjectPtr<AWorkshop4Character> Player = Cast<AWorkshop4Character>(OtherActor);
	if(Player)
	{
		UE_LOG(LogTemp,Warning,TEXT("collison"))
		Player->Ragdoll();
		Player->Play = false;
	}

	
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();


	Collision->OnComponentBeginOverlap.AddDynamic(this,&AObstacle::OnBoxOverlap);
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

