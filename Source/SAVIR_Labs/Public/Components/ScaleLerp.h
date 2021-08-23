// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScaleLerp.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SAVIR_LABS_API UScaleLerp : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UScaleLerp();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void ScaleCircle(float DeltaTime);

	void MinimizeCircle(float DeltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//Variables
	UPROPERTY()
	UStaticMeshComponent* Circle;

	UPROPERTY(EditAnyWhere)
	FVector EndScale = FVector(1, 1, 1);

	UPROPERTY(EditAnyWhere)
	float LerpDuration = 1.0f;

	UPROPERTY(EditAnyWhere)
	float WaitTime = 1.0f;

	float TimeElapsed = 0;

	FVector CurrentScale;
	FVector BeginScale;
};
