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
	AOverlappingActors();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* LiquidMesh;

protected:
	virtual void BeginPlay() override;

	
};
