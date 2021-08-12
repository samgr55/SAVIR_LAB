// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GeneralInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class SAVIR_LABS_API UGeneralInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetUpWidget(FString InDescription, UImage* InImage);
	
	
protected:
	virtual void NativeOnInitialized() override;

private:
	FString Description;
	UPROPERTY(meta = (BindWidget))
	UImage* InfoImage;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DescriptionText;

	
	
	
};
