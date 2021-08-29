// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WatchWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBox.h"

void UWatchWidget::RegisterTime()
{

	if(!TimeTable || ! TimerText)
	{
		UE_LOG(LogTemp, Error, TEXT("Widgets Not Created in BP in UWatchWidget::NativeOnInitialized"));
		return;
	}
	int32 Sec = FMath::Floor(TimeElapsed);
	int32 Min = Sec / 60;
	Sec = Sec % 60;
	auto Text = FString(FString::FromInt(Min)) + " : " + FString(FString::FromInt(Sec));
	auto HBox = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
	auto No = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	auto Time = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());

	if(!HBox || !No || !Time)
	{
		UE_LOG(LogTemp, Error, TEXT("Error Creating Widgets in UWatchWidget::RegisterTime"));
		return;
	}

	No->SetText(FText::FromString("(" + FString::FromInt(TableIndex) + ")  "));
	No->Font.Size = 30;
	No->Font.OutlineSettings.OutlineSize = 2;

	Time->SetText(FText::FromString(Text));
	Time->Font.Size = 30;
	Time->Font.OutlineSettings.OutlineSize = 2;

	HBox->AddChild(No);
	HBox->AddChild(Time);

	if(!TimeTable)
	{
		UE_LOG(LogTemp, Error, TEXT("TimeTable is not regestred in BP in UWatchWidget::RegisterTime"));
		return;
	}

	TimeTable->AddChild(HBox);
	TableIndex++;
	
}

void UWatchWidget::StartTimer()
{
	bMeasureTime = true;
}

void UWatchWidget::StopTimer()
{
	bMeasureTime = false;
}

void UWatchWidget::ResetTimer()
{
	TimeElapsed = 0;
}

void UWatchWidget::ResetRegisteredTime()
{
	for(int32 i = 1 ; i < TableIndex; i++)
	TimeTable->RemoveChildAt(i);
	TableIndex = 1;
}

void UWatchWidget::SkipToSec(int32 Sec)
{
	TimeElapsed = Sec;
}

void UWatchWidget::TrackTime()
{
	if(!bIsTimerWorking)
	{
		StartTimer();
		bIsTimerWorking = true;
	}
	else
	{
		StopTimer();
		bIsTimerWorking = false;
	}
}

void UWatchWidget::NativeTick(const FGeometry& MovieSceneBlends, float InDeltaTime)
{
	Super::NativeTick(MovieSceneBlends, InDeltaTime);
	if(bMeasureTime)
	{
		TimeElapsed += InDeltaTime;
		int32 Seconds = FMath::Floor(TimeElapsed);
		int32 Min = Seconds / 60;
		Seconds = Seconds % 60;
		auto Text = FString(FString::FromInt(Min)) + " : " + FString(FString::FromInt(Seconds));
		TimerText->SetText(FText::FromString(Text));
	}
}

void UWatchWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	TableIndex = 1;

	bIsTimerWorking = false;
	
	if(!TimeTable || ! TimerText)
	{
		UE_LOG(LogTemp, Error, TEXT("Widgets Not Created in BP in UWatchWidget::NativeOnInitialized"));
	}
}
