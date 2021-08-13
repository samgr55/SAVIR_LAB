// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "General/InformationActor.h"

#include "LabToolContainer.generated.h"

UCLASS()
class SAVIR_LABS_API ALabToolContainer : public AInformationActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALabToolContainer();

	UPROPERTY()
	AActor* CurrentParent;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

private:
	
	UPROPERTY()
	AActor* OriginalParent;

	FVector OriginalPosition;
	FQuat OriginalRotation;

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
