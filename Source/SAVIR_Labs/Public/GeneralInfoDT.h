// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GeneralInfoDT.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct SAVIR_LABS_API FGeneralInfoDT : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category=Data)
	FString Name;
	UPROPERTY(EditDefaultsOnly, Category=Data)
	FString Description;
	UPROPERTY(EditDefaultsOnly, Category=Data)
	UMaterial* Image;
};
