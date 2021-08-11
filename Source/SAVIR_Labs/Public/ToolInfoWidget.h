// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "LabTools/LabTool.h"

#include "ToolInfoWidget.generated.h"

UCLASS()
class SAVIR_LABS_API UToolInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetUpWidget(ALabTool* Tool);

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Name;


	UPROPERTY(meta = (BindWidget))
	UTextBlock* Description;

	
	
	// UPROPERTY(meta = (BindWidget))
	// UImage* ElementImage;
};
