// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PawnPlayer.h"
#include "Components/BoxComponent.h"
#include "Objects/Ball.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
APawnPlayer::APawnPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create BoxComponent and set as RootComponent for the Actor
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;

	// Create StaticMeshComponent and Attach to BoxComponent
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(BoxCollision);

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = BoxCollision;
}

// Called when the game starts or when spawned
void APawnPlayer::BeginPlay()
{
	Super::BeginPlay();

	// Bind function OnActorBeginOverlap with your class function OnOverlap
	this->OnActorBeginOverlap.AddDynamic(this, &APawnPlayer::OnOverlap);
	
}

// Called every frame
void APawnPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APawnPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &APawnPlayer::MoveLeftRight);

}

// Called to move on X axis
void APawnPlayer::MoveLeftRight(float AxisValue)
{
	FVector Direction = FVector(1, 0, 0);

	AddMovementInput(Direction, AxisValue);
}

// Called when an overlap happens
void APawnPlayer::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
	if (auto Ball = Cast<ABall>(OtherActor)) {
		FVector ReflectionVector = FVector(Ball->StaticMesh->GetPhysicsLinearVelocity().X + this->GetVelocity().X, -Ball->StaticMesh->GetPhysicsLinearVelocity().Y, 0);
		Ball->StaticMesh->SetPhysicsLinearVelocity(ReflectionVector.GetSafeNormal()	* Ball->Speed);
	}
}

