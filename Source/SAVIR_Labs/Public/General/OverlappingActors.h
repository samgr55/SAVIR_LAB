// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "InformationActor.h"
#include "GameFramework/Actor.h"
#include "OverlappingActors.generated.h"

UCLASS()
class SAVIR_LABS_API AOverlappingActors : public AInformationActor
{
	GENERATED_BODY()

public:
	//Variables
	// UPROPERTY()
	// AActor* CurrentParent;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	// bool bCanBeGrabbed;

	//Functions
	// Sets default values for this actor's properties
	AOverlappingActors();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* LiquidMesh;
};
