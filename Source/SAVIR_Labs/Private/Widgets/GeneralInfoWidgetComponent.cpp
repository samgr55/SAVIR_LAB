// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GeneralInfoWidgetComponent.h"

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
	if(!WidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Empty WidgetClass in UGeneralInfoWidgetComponent::BeginPlay"));
		return;
	}
	InfoWidget = Cast<UGeneralInfoWidget>(GetWidget());

	if(!InfoWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wrong widget type widget must be UGeneralInfoWidget in UGeneralInfoWidgetComponent::BeginPlay"));
		return;
	}

	InfoWidget->RemoveFromViewport();

	InformationActor = Cast<AInformationActor>(GetOwner());

	if(!InformationActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wrong Actor type widget must be AInformationActor in UGeneralInfoWidgetComponent::BeginPlay"));
		return;
	}

	InfoWidget->SetUpWidget(InformationActor->GetDescription(), InformationActor->GetImageDescription());
	
}
