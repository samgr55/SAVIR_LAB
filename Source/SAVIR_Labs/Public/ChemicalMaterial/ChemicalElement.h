// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/Image.h"
#include "Engine/DataTable.h"

#include "ChemicalElement.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct SAVIR_LABS_API FChemicalElement: public FTableRowBase
{
	GENERATED_BODY()


public:

	friend bool operator==(const FChemicalElement& Lhs, const FChemicalElement& RHS)
	{
		return Lhs.AtomicNumber == RHS.AtomicNumber;
	}

	friend bool operator!=(const FChemicalElement& Lhs, const FChemicalElement& RHS)
	{
		return !(Lhs == RHS);
	}

	UPROPERTY(EditDefaultsOnly, Category=Data)
	FString Symbol;
	UPROPERTY(EditDefaultsOnly, Category=Data)
	FString Name;
	UPROPERTY(EditDefaultsOnly, Category=Data)
	int32 AtomicNumber;
	UPROPERTY(EditDefaultsOnly, Category=Data)
	float Weight;
	UPROPERTY(EditDefaultsOnly, Category=Data)
	FString State;
	UPROPERTY(EditDefaultsOnly, Category=Data)
	FString Description;
	UPROPERTY(EditDefaultsOnly, Category=Data)
	FString Family;
	UPROPERTY(EditDefaultsOnly, Category=Data)
	UImage* Image;
};
