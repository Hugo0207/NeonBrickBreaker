// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Brick.generated.h"

UCLASS()
class BRICKBREAKER_API ABrick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrick();

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Particles")
	class UParticleSystem* Particle;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* DestroySound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Strength;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Update brick color
	UFUNCTION()
	void UpdateBrickColor();

	// Called on overlap with another object
	UFUNCTION()
	void OnOverlap(AActor* MyActor, AActor* OtherActor);

};
