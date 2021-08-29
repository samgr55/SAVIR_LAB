// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DiffusionDataEntry.h"

void UDiffusionDataEntry::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(!HighTempSlider || !LowTempSlider || !RoomTempSlider)
	{
		return;
	}

	if(!HighAOD || !LowAOD || !RoomAOD)
	{
		return;
	}

	if(!HighROD || !LowROD || !RoomROD)
	{
		return;
	}
	
	
	HighTempSlider->OnValueChanged.AddDynamic(this, &UDiffusionDataEntry::OnHighChanged);
	LowTempSlider->OnValueChanged.AddDynamic(this, &UDiffusionDataEntry::OnLowChanged);
	RoomTempSlider->OnValueChanged.AddDynamic(this, &UDiffusionDataEntry::OnRoomChanged);
}

void UDiffusionDataEntry::NativeConstruct()
{
	Super::NativeConstruct();
	
	LowTempSlider->SetValue(RadiusAt_LowTemp);
	RoomTempSlider->SetValue(RadiusAt_RoomTemp);
	HighTempSlider->SetValue(RadiusAt_HighTemp);
}

void UDiffusionDataEntry::NativeDestruct()
{
	Super::NativeDestruct();
}

void UDiffusionDataEntry::OnLowChanged_Implementation(float Value)
{
	RadiusAt_LowTemp = Value;
	float AOD = Value * Value * 3.14;
	float ROD = AOD / 1.5;
	LowAOD->SetText(FText::AsNumber(AOD));
	LowROD->SetText(FText::AsNumber(ROD));
}

void UDiffusionDataEntry::OnHighChanged_Implementation(float Value)
{
	RadiusAt_HighTemp = Value;
	float AOD = Value * Value * 3.14;
	float ROD = AOD / 1.5;
	HighAOD->SetText(FText::AsNumber(AOD));
	HighROD->SetText(FText::AsNumber(ROD));
}

void UDiffusionDataEntry::OnRoomChanged_Implementation(float Value)
{
	RadiusAt_RoomTemp = Value;
	float AOD = Value * Value * 3.14;
	float ROD = AOD / 1.5;
	RoomAOD->SetText(FText::AsNumber(AOD));
	RoomROD->SetText(FText::AsNumber(ROD));
}
