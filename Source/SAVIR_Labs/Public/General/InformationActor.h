// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IInformative.h"
#include "GameFramework/Actor.h"
#include "Widgets/GeneralInfoWidgetComponent.h"
#include "InformationActor.generated.h"

class UWidgetComponent;
UCLASS()
class SAVIR_LABS_API AInformationActor : public AActor, public IIInformative
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInformationActor();

protected:
	//Variables
	FString Description;
	
	UPROPERTY()
	UImage* ImageDescription;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UGeneralInfoWidgetComponent* WidgetComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
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
