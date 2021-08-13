// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "InstructionTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class SAVIR_LABS_API AInstructionTriggerBox : public ATriggerBox
{
	GENERATED_BODY()


public:
	AInstructionTriggerBox();

	UFUNCTION()
	void OnOverlap(AActor* ThisActor, AActor* OtherActor);

	UPROPERTY(EditInstanceOnly, Category=Data)
	FString Title;
	UPROPERTY(EditInstanceOnly, Category=Data)
	TArray<AActor*>LookAtActors;
	UPROPERTY(EditInstanceOnly, Category=Data)
	TArray<float> LookAtTimeInSecond;
	UPROPERTY(EditInstanceOnly, Category=Data)
	TArray<FString> Narrative;
	UPROPERTY(EditInstanceOnly, Category=Data)
	TArray<float> NarrativeTimeInMSecond;
	
	
	
};
