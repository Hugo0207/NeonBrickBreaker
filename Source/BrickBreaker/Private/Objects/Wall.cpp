// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Wall.h"
#include "Objects/Ball.h"
#include "Player/PawnPlayer.h"
#include "Components/BoxComponent.h"

// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create BoxComponent and set as RootComponent for the Actor
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;

	// Create StaticMeshComponent and Attach to BoxComponent
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(BoxCollision);

}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind function OnActorBeginOverlap with your class function OnOverlap
	this->OnActorBeginOverlap.AddDynamic(this, &AWall::OnOverlap);
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when an overlap happens
void AWall::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
	if (auto Ball = Cast<ABall>(OtherActor)) {
		Ball->Speed = 1.05 * Ball->Speed;
		FVector ReflectionVector = -2 * Ball->StaticMesh->GetPhysicsLinearVelocity() * HitNormal + Ball->StaticMesh->GetPhysicsLinearVelocity();
		Ball->StaticMesh->SetPhysicsLinearVelocity(ReflectionVector.GetSafeNormal() * Ball->Speed);
	}
}

