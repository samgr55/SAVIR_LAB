// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InstructionsHUD.h"


AInstructionsHUD::AInstructionsHUD()
{
}

void AInstructionsHUD::BeginPlay()
{
	Super::BeginPlay();

	if(!InstructionsWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("InstructionsWidgetClass is NULL in AInstructionsHUD::BeginPlay"));
		return;
	}
	InstructionsWidget = CreateWidget<UInstructionsWidget>(GetWorld(), InstructionsWidgetClass);
	if(!InstructionsWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Create InstructionsWidget in AInstructionsHUD::BeginPlay"));
		return;
	}
	InstructionsWidget->AddToViewport();
}
