// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "ChemicalContainer.generated.h"


class AChemicalSubstance;
class UUserWidget;
class UStaticMeshComponent;

UCLASS()
class SAVIR_LABS_API AChemicalContainer : public AActor
{
	GENERATED_BODY()
	
	public:	
	// Sets default values for this actor's properties
	AChemicalContainer();

	UFUNCTION()
	void MoveTo(AChemicalContainer* NewContainer, bool bMoveAll = true, float MoveQuantity = 0.0);

	void ShowWidget();
	void HideWidget();

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	AActor* CurrentParent;

	
	private:

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditAnywhere, Category = Data)
	AChemicalSubstance* Substance;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	UWidgetComponent* WidgetComponent;

	UPROPERTY()
	AActor* OriginalParent;

	FVector OriginalPosition;
	FQuat OriginalRotation;
};
