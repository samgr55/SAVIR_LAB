// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"
#include "LabTool.generated.h"


USTRUCT(BlueprintType)
struct SAVIR_LABS_API FLabTools:public FTableRowBase
{
	GENERATED_BODY()

	friend bool operator==(const FLabTools& LHS, const FLabTools& RHS)
	{
		return LHS.ToolId == RHS.ToolId;
	}

	friend bool operator!=(const FLabTools& LHS, const FLabTools& RHS)
	{
		return !(LHS == RHS);
	}

	UPROPERTY(EditDefaultsOnly, Category=Data)
	FString Name;

	UPROPERTY(EditDefaultsOnly, Category=Data)
	FString Description;

	UPROPERTY(EditDefaultsOnly, Category=Data)
	int32 ToolId;

	UPROPERTY(EditDefaultsOnly, Category=Data)
	UTexture2D* Image;
};

