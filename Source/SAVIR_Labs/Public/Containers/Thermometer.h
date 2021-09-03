// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "General/OverlappingActors.h"

#include "Thermometer.generated.h"

class AWaterContainer;
class USphereComponent;
class UTextRenderComponent;

UCLASS()
class SAVIR_LABS_API AThermometer : public AOverlappingActors
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AThermometer();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetTemperature();
	void SetTemperature(float temperature);

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* Text;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Variables
	UPROPERTY(VisibleAnywhere)
	USphereComponent* MyCollisionSphere;

	float SphereRaidus = 5.0f;
	
	float Temperature = 0.0f;

	bool bIsOverlappingWithWaterContainer;

	AWaterContainer* WaterContainer;


public:
	virtual void StartAction_Implementation() override;
	virtual void StopAction_Implementation() override;
	
};

