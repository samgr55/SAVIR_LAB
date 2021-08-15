// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GeneralInfoWidget.h"

void UGeneralInfoWidget::SetUpWidget(FString InDescription, UImage* InImage)
{
	if(!InImage)
	{
		UE_LOG(LogTemp, Error, TEXT("InfoImage is nullptr in UGeneralInfoWidget::SetUpWidget"));
		return;
	}
	if(!InfoImage || !DescriptionText)
	{
		UE_LOG(LogTemp, Error, TEXT("InfoImage and DescriptionText must set in designer in UGeneralInfoWidget::SetUpWidget"));
		return;
	}
	this->InfoImage->SetBrush(InImage->Brush);
	this->Description = InDescription;
	DescriptionText->SetText(FText::FromString(InDescription));
}

void UGeneralInfoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(!InfoImage || !DescriptionText)
	{
		UE_LOG(LogTemp, Error, TEXT("InfoImage and DescriptionText must set in designer in UGeneralInfoWidget::NativeOnInitialized"));
		return;
	}
	
}
