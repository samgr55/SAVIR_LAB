// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IInformative.h"
#include "GameFramework/Actor.h"
#include "InformationActor.generated.h"

UCLASS()
class SAVIR_LABS_API AInformationActor : public AActor, public IIInformative
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInformationActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FString Description;
	UPROPERTY()
	UImage* ImageDescription;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual FString GetDescription_Implementation() override;
	virtual UImage* GetImageDescription_Implementation() override;
};
