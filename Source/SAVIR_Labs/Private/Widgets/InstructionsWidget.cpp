// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/InstructionsWidget.h"

void UInstructionsWidget::StartNarrative(FString InTitle, TArray<FString>* InNarrative,
	TArray<float>* InNarrativeTimeInMSecond)
{
	Title = InTitle;
	Narrative = InNarrative;
	NarrativeTimeInMSecond = InNarrativeTimeInMSecond;
	TitleText->SetText(FText::FromString(Title));
	NarrativeViewer();
}

void UInstructionsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(!TitleText || !NarrativeText)
	{
		UE_LOG(LogTemp, Error, TEXT("TitleText or NarrativeText wasnt created in Designer in UInstructionsWidget::NativeOnInitialized"));
		return;
	}
	TitleText->SetText(FText::FromString(""));
	NarrativeText->SetText((FText::FromString("")));
}

void UInstructionsWidget::NarrativeViewer()
{
	if(Index >= Narrative->Num())
	{
		TitleText->SetText(FText::FromString(""));
		NarrativeText->SetText((FText::FromString("")));
		return;
	}
	NarrativeText->SetText(FText::FromString(Narrative->GetData()[Index]));
	GetOwningPlayer()->GetWorldTimerManager().SetTimer(NarrativeTimerHandle, this,
		&UInstructionsWidget::NarrativeViewer, NarrativeTimeInMSecond->GetData()[Index]/1000.f);
	Index++;
}
