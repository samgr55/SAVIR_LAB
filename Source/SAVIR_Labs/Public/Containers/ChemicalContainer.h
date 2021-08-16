// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "General/Action.h"

#include "General/InformationActor.h"
#include "ChemicalContainer.generated.h"


class UDataTable;
class UChemicalSubstance;
class UUserWidget;
class UStaticMeshComponent;
class UWidgetComponent;

UCLASS()
class SAVIR_LABS_API AChemicalContainer : public AInformationActor, public IAction 
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AChemicalContainer();

	UPROPERTY()
	AActor* CurrentParent;

	virtual void StartAction_Implementation() override;
	virtual void StopAction_Implementation() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnParticleSmoke();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UParticleSystemComponent* SmokeParticle;

private:
	
	
	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY()
	AActor* OriginalParent;

	FVector OriginalPosition;
	FQuat OriginalRotation;

	UPROPERTY()
	UStaticMeshComponent* CapMesh;
	
};
