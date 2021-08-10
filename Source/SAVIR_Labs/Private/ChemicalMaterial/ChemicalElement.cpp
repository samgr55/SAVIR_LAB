// Fill out your copyright notice in the Description page of Project Settings.


#include "SAVIR_Labs/Public/ChemicalMaterial/ChemicalElement.h"

FChemicalElement* AChemicalElements::GetElementByAtomicNumber(int32 AtomicNumber)
{
	auto Result =  ElementsArray.FindByPredicate([AtomicNumber](FChemicalElement Element){return AtomicNumber == Element.AtomicNumber;});
	return Result;
}

FChemicalElement* AChemicalElements::GetElementBySymbol(FString Symbol)
{
	auto Result = ElementsArray.FindByPredicate([Symbol](FChemicalElement RHS){return RHS.Symbol.ToLower() == Symbol.ToLower();});
	return Result;
}

FChemicalElement* AChemicalElements::GetElementByName(FString Name)
{
	auto Result = ElementsArray.FindByPredicate([Name](FChemicalElement RHS){return RHS.Name.ToLower() == Name.ToLower();});
	return Result;
}
