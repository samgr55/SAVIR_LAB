// Fill out your copyright notice in the Description page of Project Settings.


#include "Containers/StopWatch.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/DiffusionDataEntry.h"
#include "Widgets/WatchWidget.h"

void AStopWatch::StartAction_Implementation()
{
	Super::StartAction_Implementation();
	if(!WatchWidget)
	{
		return;
	}
	WatchWidget->AddToViewport();
}

void AStopWatch::StopAction_Implementation()
{
	Super::StopAction_Implementation();
	if(!WatchWidget)
	{
		return;
	}
	
	WatchWidget->RemoveFromViewport();
}

void AStopWatch::BeginPlay()
{
	Super::BeginPlay();
	if(!WatchWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("WatchWidgetClass not assigned! in BP! AStopWatch::BeginPlay"));
		return;
	}
	WatchWidget = CreateWidget<UWatchWidget>(GetWorld(), WatchWidgetClass, FName(FString("WatchWid")));
	if(!WatchWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Create WatchWidget! AStopWatch::BeginPlay"));
	}
	
	if(!DiffusionDataEntryWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("DiffusionDataEntryWidgetClass not assigned! in BP! AStopWatch::BeginPlay"));
		return;
	}
	DiffusionDataEntryWidget = CreateWidget<UDiffusionDataEntry>(GetWorld(), DiffusionDataEntryWidgetClass, FName(FString("DiffusionDataEntryWidget")));
	if(!DiffusionDataEntryWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Create WatchWidget! AStopWatch::BeginPlay"));
	}
}


