// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "IInformative.h"
#include "GameFramework/Actor.h"
#include "InformationActor.generated.h"

struct FGeneralInfoDT;
class UDataTable;
class UGeneralInfoWidgetComponent;

UCLASS()
class SAVIR_LABS_API AInformationActor : public AActor, public IIInformative, public IAction 
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties

	AInformationActor();

	virtual void StartAction_Implementation() override;
	virtual void StopAction_Implementation() override;
	

protected:
	//Variables

	UPROPERTY(VisibleAnywhere)
	USceneComponent* InformationActorRootComponent;

	UPROPERTY(VisibleAnywhere)
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

	UPROPERTY()
	AActor* OriginalParent;

	FVector OriginalPosition;
	FQuat OriginalRotation;
	
public:
	//Functions
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetUpInfo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeGrabbed;

	void ResetToOriginalPosition();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual FString GetDescription_Implementation() override;
	virtual UImage* GetImageDescription_Implementation() override;

	UPROPERTY()
	AActor* CurrentParent;


	virtual void ShowWidget();
	virtual void HideWidget();

private:



public:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	UStaticMeshComponent* GetStaticMeshComponent() const;
};
