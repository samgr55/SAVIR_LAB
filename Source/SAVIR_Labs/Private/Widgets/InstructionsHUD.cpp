// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InstructionsHUD.h"


AInstructionsHUD::AInstructionsHUD()
{
	
}

void AInstructionsHUD::ShowActionWidget(const FString& Message)
{
	if(InstructionsWidget->IsInViewport())
	{
		InstructionsWidget->RemoveFromViewport();
	}
	
	ActionWidget->SetWarningMessage(Message);
	if(!ActionWidget->IsInViewport())
		ActionWidget->AddToViewport();
}

void AInstructionsHUD::HideActionWidget()
{
	if(ActionWidget->IsInViewport())
		ActionWidget->RemoveFromViewport();
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

	if(!ActionWidgetBPClass)
	{
		UE_LOG(LogTemp, Error, TEXT("ActionWidgetBPClass is NULL in AInstructionsHUD::BeginPlay"));
		return;
	}
	ActionWidget = CreateWidget<UActionWidget>(GetWorld(), ActionWidgetBPClass);
	if(!ActionWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Create ActionWidget in AInstructionsHUD::BeginPlay"));
		return;
	}

}
