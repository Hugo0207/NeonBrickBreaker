// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/BallDestroyer.h"
#include "Objects/Ball.h"
#include "Components/BoxComponent.h"

// Sets default values
ABallDestroyer::ABallDestroyer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create BoxComponent and set as RootComponent for the Actor
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;
}

// Called when the game starts or when spawned
void ABallDestroyer::BeginPlay()
{
	Super::BeginPlay();

	// Bind function OnActorBeginOverlap with your class function OnOverlap
	this->OnActorBeginOverlap.AddDynamic(this, &ABallDestroyer::OnOverlap);
	
}

// Called every frame
void ABallDestroyer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when an overlap happens
void ABallDestroyer::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
	if (auto Ball = Cast<ABall>(OtherActor)) {
		Ball->Destroy();
		// Check object to spawn is not null
		if (ObjectToSpawn)
			GetWorld()->SpawnActor<AActor>(ObjectToSpawn, FVector(0, 0, 70), FRotator(0, 0, 0));
	}
}

