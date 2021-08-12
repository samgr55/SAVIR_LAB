// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IInformative.h"
#include "GameFramework/Actor.h"
#include "InformationActor.generated.h"

class UGeneralInfoWidgetComponent;
UCLASS(Blueprintable)
class SAVIR_LABS_API AInformationActor : public AActor, public IIInformative
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInformationActor();

	UPROPERTY()
	UGeneralInfoWidgetComponent* WidgetComponent;
	
	
protected:
	//Variables
	FString Description;
	
	UPROPERTY()
	UImage* ImageDescription;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	//Functions
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual FString GetDescription_Implementation() override;
	virtual UImage* GetImageDescription_Implementation() override;

	void ShowWidget();
	void HideWidget();
};
