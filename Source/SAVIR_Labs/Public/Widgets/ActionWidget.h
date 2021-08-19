// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ActionWidget.generated.h"

/**
 * 
 */
UCLASS()
class SAVIR_LABS_API UActionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite,meta =(BindWidget))
	UTextBlock* WarningMessageText;

private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	FString WarningMessage;
public:
	FString GetWarningMessage() const;
	void SetWarningMessage(const FString& InWarningMessage);
};
