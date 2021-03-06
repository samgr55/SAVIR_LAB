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
class SAVIR_LABS_API AChemicalContainer : public AInformationActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AChemicalContainer();

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
	
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	UStaticMeshComponent* CapMesh;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	FVector CapMeshOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	FString ActionMessage;
	
	
};
