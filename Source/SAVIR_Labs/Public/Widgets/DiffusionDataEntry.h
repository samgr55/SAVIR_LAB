// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "DiffusionDataEntry.generated.h"

/**
 * 
 */
UCLASS()
class SAVIR_LABS_API UDiffusionDataEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnLowChanged(float Value);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnHighChanged(float Value);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnRoomChanged(float Value);
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	
private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	float RadiusAt_LowTemp;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	float RadiusAt_RoomTemp;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	float RadiusAt_HighTemp;

	UPROPERTY(meta=(BindWidget))
	USlider* LowTempSlider;

	UPROPERTY(meta=(BindWidget))
	USlider* RoomTempSlider;

	UPROPERTY(meta=(BindWidget))
	USlider* HighTempSlider;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* LowAOD;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* RoomAOD;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* HighAOD;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* LowROD;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* RoomROD;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* HighROD;

	
};
