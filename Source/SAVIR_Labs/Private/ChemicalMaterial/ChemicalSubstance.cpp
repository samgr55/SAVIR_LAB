// Fill out your copyright notice in the Description page of Project Settings.


#include "SAVIR_Labs/Public/ChemicalMaterial/ChemicalSubstance.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AChemicalSubstance::AChemicalSubstance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

AChemicalSubstance* AChemicalSubstance::React(AChemicalSubstance* OtherSubstance)
{
	auto X = GetWorld()->SpawnActor<AChemicalSubstance>(AChemicalSubstance::StaticClass());
	return X;
}

// Called when the game starts or when spawned
void AChemicalSubstance::BeginPlay()
{
	Super::BeginPlay();
	ChemicalElement = ElementsArray->GetElementByAtomicNumber(SubstanceID);
	Description = ChemicalElement->Description;
	ImageDescription = NewObject<UImage>(GetWorld());
	ImageDescription->SetBrushFromTexture(ChemicalElement->Image);
}

// Called every frame
void AChemicalSubstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

