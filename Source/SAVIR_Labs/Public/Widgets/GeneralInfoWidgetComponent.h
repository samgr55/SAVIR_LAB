// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeneralInfoWidget.h"
#include "Components/WidgetComponent.h"
#include "General/InformationActor.h"
#include "GeneralInfoWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class SAVIR_LABS_API UGeneralInfoWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:

	void ShowWidget();

	void HideWidget();
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UGeneralInfoWidget* InfoWidget;

	UPROPERTY()
	AInformationActor* InformationActor;
};
