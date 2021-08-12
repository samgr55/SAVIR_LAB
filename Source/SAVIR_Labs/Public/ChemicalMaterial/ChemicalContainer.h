// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "General/InformationActor.h"
#include "ChemicalContainer.generated.h"


struct FChemicalElement;
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

	UPROPERTY()
	AActor* CurrentParent;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category=Data)
	UDataTable* DataTable;
	
	FChemicalElement* ChemicalElement;
	
	private:

	UPROPERTY(EditAnywhere, Category= Data)
	int32 SubstanceID = 1;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY()
	AActor* OriginalParent;

	FVector OriginalPosition;
	FQuat OriginalRotation;
	
};
