// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ChemicalInfoWidgets.h"

void UChemicalInfoWidgets::SetUpWidget(FChemicalElement* Element)
{

	if(!Symbol || !Name || !AtomicNumber || !Weight || !ElementImage) return;

	if(!Element) return;
	
	Symbol->SetText(FText::FromString(Element->Symbol));
	Name->SetText(FText::FromString(Element->Name));
	AtomicNumber->SetText(FText::FromString(FString::FromInt(Element->AtomicNumber)));
	Weight->SetText(FText::FromString(FString::FromInt(Element->Weight)));
	ElementImage->SetBrushFromTexture(Element->Image);
}
