// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionWidget.h"
#include "InstructionsWidget.h"
#include "GameFramework/HUD.h"
#include "InstructionsHUD.generated.h"

/**
 * 
 */
UCLASS()
class SAVIR_LABS_API AInstructionsHUD : public AHUD
{
	GENERATED_BODY()

public:
	AInstructionsHUD();
	
	UInstructionsWidget* GetInstructionsWidget()
	{
		return InstructionsWidget;
	}

	UFUNCTION(BlueprintCallable)
	void ShowActionWidget(const FString& Message);
	UFUNCTION(BlueprintCallable)
	void HideActionWidget();
	
protected:
	virtual void BeginPlay() override;


private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInstructionsWidget> InstructionsWidgetClass;
	
	UPROPERTY()
	UInstructionsWidget* InstructionsWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UActionWidget> ActionWidgetBPClass;
	
	UPROPERTY()
	UActionWidget* ActionWidget;
	
};
