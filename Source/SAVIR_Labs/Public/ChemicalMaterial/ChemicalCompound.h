// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ChemicalMaterial/ChemicalElement.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "ChemicalCompound.generated.h"

/**
 * 
 */
USTRUCT()
struct SAVIR_LABS_API FChemicalCompound : public FChemicalElement
{
	GENERATED_BODY()

	TArray<FChemicalElement*> Elements;
	
};
