// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ChemicalElement.h"
#include "GameFramework/Actor.h"
#include "General/InformationActor.h"

#include "ChemicalSubstance.generated.h"

struct FChemicalElement;
UCLASS()
class SAVIR_LABS_API AChemicalSubstance : public AInformationActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChemicalSubstance();

	AChemicalSubstance* React(AChemicalSubstance* OtherSubstance);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Data)
	AChemicalElements* ElementsArray;

	FChemicalElement* ChemicalElement;
	
private:

	UPROPERTY(EditAnywhere, Category= Data)
	int32 SubstanceID = 1;
	
	UPROPERTY(EditAnywhere, Category=Data)
	float Quantity;
};
