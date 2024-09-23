// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallDestroyer.generated.h"

UCLASS()
class BRICKBREAKER_API ABallDestroyer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallDestroyer();

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxCollision;

	// Dynamic actor variable you can acces in UE editor
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ObjectToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called on overlap with another object
	UFUNCTION()
	void OnOverlap(AActor* MyActor, AActor* OtherActor);

};
