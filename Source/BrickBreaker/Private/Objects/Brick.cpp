// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Brick.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Objects/Ball.h"


// Sets default values
ABrick::ABrick()
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
void ABrick::BeginPlay()
{
	Super::BeginPlay();

	// Bind function OnActorBeginOverlap with your class function OnOverlap
	this->OnActorBeginOverlap.AddDynamic(this, &ABrick::OnOverlap);

	// Update brick color at the beginning of the game
	this->UpdateBrickColor();
}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Update brick color based on its current strength
void ABrick::UpdateBrickColor()
{
	UMaterialInterface* GreenMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Materials/GlowGreenMat.GlowGreenMat'"));
	UMaterialInterface* YellowMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Materials/GlowYellowMat.GlowYellowMat'"));
	UMaterialInterface* OrangeMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Materials/GlowOrangeMat.GlowOrangeMat'"));
	UMaterialInterface* RedMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("Material'/Game/Materials/GlowRedMat.GlowRedMat'"));
	
	switch (Strength) {

	case 4:
		StaticMesh->SetMaterial(0, GreenMaterial);
		break;

	case 3:
		StaticMesh->SetMaterial(0, YellowMaterial);
		break;

	case 2:
		StaticMesh->SetMaterial(0, OrangeMaterial);
		break;

	case 1:
		StaticMesh->SetMaterial(0, RedMaterial);
		break;

	default:
		break;
	}
}

// Called when an overlap happens
void ABrick::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
	if (auto Ball = Cast<ABall>(OtherActor)) {
		Strength -= 1;
		if (Strength == 0) {
			if (Particle != NULL)
			{
				// Transform --> Location, Rotation, Scale
				FTransform ParticleT;
				// Spawn Location
				ParticleT.SetLocation(this->GetActorLocation());
				// World Size Particule
				ParticleT.SetScale3D(FVector(1, 1, 1));
				// Spawn Particule
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, ParticleT, true);
			}

			if (DestroySound) {
				UGameplayStatics::PlaySound2D(GetWorld(), DestroySound);
			}
			Destroy();
			Ball->Score += 300;
		}
		else {
			Ball->Score += 100;
			this->UpdateBrickColor();
		}
	}
}

