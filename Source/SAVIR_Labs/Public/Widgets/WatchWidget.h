// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "WatchWidget.generated.h"

/**
 * 
 */
UCLASS()
class SAVIR_LABS_API UWatchWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterTime();
	UFUNCTION(BlueprintCallable)
	void ResetTimer();
	UFUNCTION(BlueprintCallable)
	void ResetRegisteredTime();
	UFUNCTION(BlueprintCallable)
	void SkipToSec(int32 Sec);
	UFUNCTION(BlueprintCallable)
	void TrackTime();

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	void StartTimer();
	void StopTimer();
	
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* TimeTable;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TimerText;

	int32 TableIndex;

	float TimeElapsed;
	
	bool bMeasureTime;

	bool bIsTimerWorking;
	
	
};
