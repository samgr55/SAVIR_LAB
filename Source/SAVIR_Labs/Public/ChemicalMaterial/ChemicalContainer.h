// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "General/InformationActor.h"
#include "ChemicalContainer.generated.h"


class AChemicalSubstance;
class UUserWidget;
class UStaticMeshComponent;
class UWidgetComponent;

UCLASS()
class SAVIR_LABS_API AChemicalContainer : public AInformationActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AChemicalContainer();

	UPROPERTY()
	AActor* CurrentParent;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void MoveTo(AChemicalContainer* NewContainer, bool bMoveAll = true, float MoveQuantity = 0.0);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = Data)
	AChemicalSubstance* Substance;

	UPROPERTY()
	AActor* OriginalParent;

	FVector OriginalPosition;
	FQuat OriginalRotation;
};
