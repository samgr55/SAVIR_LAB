// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FoodContainer.generated.h"


class USphereComponent;
class UStaticMeshComponent;
UCLASS()
class SAVIR_LABS_API AFoodContainer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFoodContainer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* MyCollisionSphere;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CapMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LiquidMesh;

	float SphereRaidus = 5.0f;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
