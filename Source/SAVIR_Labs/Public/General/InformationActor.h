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

	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* InformationActorRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UGeneralInfoWidgetComponent* WidgetComponent;

	UPROPERTY(BlueprintReadWrite)
	FString Description;

	UPROPERTY(BlueprintReadWrite)
	UImage* ImageDescription;

	UPROPERTY(BlueprintReadWrite)
	FVector OriginalPosition;
	
	UPROPERTY(BlueprintReadWrite)
	FQuat OriginalRotation;

	UPROPERTY(BlueprintReadWrite)
	bool bIsShowingInfoWidget;

	UPROPERTY(BlueprintReadWrite)
	bool bIsInAction;
public:
	bool IsIsInAction() const;
protected:
	UPROPERTY(EditAnywhere, Category=Data)
	UDataTable* DataTable;

	FGeneralInfoDT* DataRow;

	UPROPERTY(EditAnywhere, Category=Data)
	int32 RowID;
	
public:

	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void SetUpInfo();

	UFUNCTION(BlueprintCallable)
	virtual void ShowWidget();

	UFUNCTION(BlueprintCallable)
	virtual void HideWidget();
	
	UFUNCTION(BlueprintCallable)
	void ResetToOriginalPosition();

	virtual FString GetDescription_Implementation() override;

	virtual UImage* GetImageDescription_Implementation() override;

	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanBeGrabbed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsGrabbedWithHand;
	
	UPROPERTY(BlueprintReadWrite)
	AActor* CurrentParent;

	bool IsShowingInfoWidget();
	
};
