// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "General/OverlappingActors.h"

#include "FoodContainer.generated.h"


class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class SAVIR_LABS_API AFoodContainer : public AOverlappingActors
{
	GENERATED_BODY()

public:
	//Variables
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CapMesh;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* MyCollisionSphere;

	//Functions
	// Sets default values for this actor's properties
	AFoodContainer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
