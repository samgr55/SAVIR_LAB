// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GeneralInfoWidgetComponent.generated.h"

class AInformationActor;
class UGeneralInfoWidget;
/**
 * 
 */
UCLASS(Blueprintable, ClassGroup=(Rendering, Common), hidecategories=(Object,Activation,"Components|Activation"), ShowCategories=(Mobility), editinlinenew, meta=(BlueprintSpawnableComponent))
class SAVIR_LABS_API UGeneralInfoWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:

	UGeneralInfoWidgetComponent();

	void SetUpWidgetComponent();
	
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
