// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GeneralInfoWidgetComponent.h"

#include "General/InformationActor.h"
#include "Widgets/GeneralInfoWidget.h"

UGeneralInfoWidgetComponent::UGeneralInfoWidgetComponent()
{
	
}

void UGeneralInfoWidgetComponent::SetUpWidgetComponent()
{
	if(!WidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Empty WidgetClass in UGeneralInfoWidgetComponent::SetUpWidgetComponent"));
		return;
	}
	InfoWidget = Cast<UGeneralInfoWidget>(GetWidget());

	if(!InfoWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("Wrong widget type widget must be UGeneralInfoWidget in UGeneralInfoWidgetComponent::SetUpWidgetComponent"));
		return;
	}

	//InfoWidget->RemoveFromViewport();

	InformationActor = Cast<AInformationActor>(GetOwner());

	if(!InformationActor)
	{
		UE_LOG(LogTemp, Error, TEXT("Wrong Actor type widget must be AInformationActor in UGeneralInfoWidgetComponent::SetUpWidgetComponent"));
		return;
	}
	InfoWidget->SetUpWidget(InformationActor->GetDescription_Implementation(), InformationActor->GetImageDescription_Implementation());
	
}

void UGeneralInfoWidgetComponent::ShowWidget()
{
	InfoWidget->AddToViewport();
}

void UGeneralInfoWidgetComponent::HideWidget()
{
	InfoWidget->RemoveFromViewport();
}

void UGeneralInfoWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	
}
