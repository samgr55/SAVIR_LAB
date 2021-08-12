// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "InstructionsWidget.generated.h"

/**
 * 
 */
UCLASS()
class SAVIR_LABS_API UInstructionsWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	void StartNarrative(FString InTitle, TArray<FString>* InNarrative, TArray<float>* InNarrativeTimeInMSecond);
	
protected:
	virtual void NativeOnInitialized() override;
	
private:

	void NarrativeViewer();
	
	FString Title;

	int32 Index = 0;

	TArray<FString>* Narrative;

	TArray<float>* NarrativeTimeInMSecond;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TitleText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* NarrativeText;

	FTimerHandle NarrativeTimerHandle;
	
	
};
