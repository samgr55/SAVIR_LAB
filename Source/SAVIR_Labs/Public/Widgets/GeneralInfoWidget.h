// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "GeneralInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class SAVIR_LABS_API UGeneralInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetUpWidget(FString Description, UImage* Image);
	
	
protected:
	virtual void NativeOnInitialized() override;

private:
	FString Description;
	UPROPERTY()
	UImage* Image;
	
};
