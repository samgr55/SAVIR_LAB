// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChemicalMaterial/ChemicalElement.h"
#include "Components/TextBlock.h"
#include "ChemicalInfoWidgets.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class SAVIR_LABS_API UChemicalInfoWidgets : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetUpWidget(FChemicalElement* Element);
	
protected:
	
	
	
private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Symbol;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Name;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AtomicNumber;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Weight;

	UPROPERTY(meta = (BindWidget))
	UImage* ElementImage;
};
