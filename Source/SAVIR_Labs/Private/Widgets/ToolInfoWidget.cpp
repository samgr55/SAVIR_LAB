// Fill out your copyright notice in the Description page of Project Settings.


#include "ToolInfoWidget.h"

void UToolInfoWidget::SetUpWidget(FLabTools* Tool)
{
	if(!Name || !Description)
	{
		return;
	}

	if(!Tool)
	{
		return;
	}
	
	Name->SetText(FText::FromString(Tool->Name));
	Description->SetText(FText::FromString(Tool->Description));
	ElementImage->SetBrushFromTexture(Tool->Image);
}
