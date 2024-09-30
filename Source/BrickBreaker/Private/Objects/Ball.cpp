// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Ball.h"
#include "Objects/Brick.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create BoxComponent and set as RootComponent for the Actor
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;

	// Create StaticMeshComponent and Attach to BoxComponent
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(BoxCollision);

	HitSound = LoadObject<USoundBase>(nullptr, TEXT("Sound'/Game/Sound/HitSound.HitSound'"));
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	// Bind function OnActorBeginOverlap with your class function OnOverlap
	this->OnActorBeginOverlap.AddDynamic(this, &ABall::OnOverlap);

	StaticMesh->SetPhysicsLinearVelocity(FVector(0, -Speed, 0));
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called when an overlap happens
void ABall::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
	if (HitSound) {
		UGameplayStatics::PlaySound2D(GetWorld(), HitSound);
	}
}

