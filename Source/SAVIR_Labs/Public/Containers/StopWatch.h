// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "General/InformationActor.h"
#include "StopWatch.generated.h"

/**
 * 
 */
class UDiffusionDataEntry;
class UWatchWidget;

UCLASS()
class SAVIR_LABS_API AStopWatch : public AInformationActor
{
	GENERATED_BODY()

public:
	virtual void StartAction_Implementation() override;
	virtual void StopAction_Implementation() override;
	
protected:
	virtual void BeginPlay() override;
	

private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
	UWatchWidget* WatchWidget;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
	UDiffusionDataEntry* DiffusionDataEntryWidget;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UWatchWidget> WatchWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDiffusionDataEntry> DiffusionDataEntryWidgetClass;
	
	
};
