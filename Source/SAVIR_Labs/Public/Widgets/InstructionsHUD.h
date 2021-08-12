// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	
protected:
	virtual void BeginPlay() override;


private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInstructionsWidget> InstructionsWidgetClass;
	
	UPROPERTY()
	UInstructionsWidget* InstructionsWidget;
	
};
