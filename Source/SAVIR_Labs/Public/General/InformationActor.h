// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IInformative.h"
#include "GameFramework/Actor.h"
#include "InformationActor.generated.h"

struct FGeneralInfoDT;
class UDataTable;
class UGeneralInfoWidgetComponent;

UCLASS(Blueprintable)
class SAVIR_LABS_API AInformationActor : public AActor, public IIInformative
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInformationActor();

protected:
	//Variables

	UPROPERTY()
	UGeneralInfoWidgetComponent* WidgetComponent;

	UPROPERTY()
	FString Description;

	UPROPERTY()
	UImage* ImageDescription;

	UPROPERTY(EditAnywhere, Category=Data)
	UDataTable* DataTable;

	FGeneralInfoDT* DataRow;

	UPROPERTY(EditAnywhere, Category=Data)
	int32 RowID;
	
public:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComp;

	//Functions
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetUpInfo();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual FString GetDescription_Implementation() override;
	virtual UImage* GetImageDescription_Implementation() override;


	virtual void ShowWidget();
	virtual void HideWidget();

private:
};
