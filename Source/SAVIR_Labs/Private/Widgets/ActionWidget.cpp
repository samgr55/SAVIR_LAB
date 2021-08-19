// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ActionWidget.h"

FString UActionWidget::GetWarningMessage() const
{
	return WarningMessage;
}

void UActionWidget::SetWarningMessage(const FString& InWarningMessage)
{
	this->WarningMessage = InWarningMessage;
	WarningMessageText->SetText(FText::FromString(InWarningMessage));
}
