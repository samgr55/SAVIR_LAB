// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "General/OverlappingActors.h"

#include "WaterContainer.generated.h"

UCLASS()
class SAVIR_LABS_API AWaterContainer : public AOverlappingActors
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	AWaterContainer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetTemperature();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Data", meta = (AllowPrivateAccess = "true"))
	float Temperature = 0.0f;
};
