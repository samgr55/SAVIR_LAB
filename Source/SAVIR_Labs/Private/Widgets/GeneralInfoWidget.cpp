// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GeneralInfoWidget.h"

void UGeneralInfoWidget::SetUpWidget(FString Description, UImage* Image)
{
	if(!Image)
	{
		UE_LOG(LogTemp, Warning, TEXT("Image is nullptr in UGeneralInfoWidget::SetUpWidget"));
		return;
	}
	this->Image = Image;
	this->Description = Description;
}

void UGeneralInfoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
}
