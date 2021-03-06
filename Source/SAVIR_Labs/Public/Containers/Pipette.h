// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "General/OverlappingActors.h"

#include "Pipette.generated.h"

class AFoodContainer;
class UScaleLerp;
class USphereComponent;
class UTextRenderComponent;

UCLASS()
class SAVIR_LABS_API APipette : public AOverlappingActors
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APipette();

	UPROPERTY(VisibleAnywhere)
	USphereComponent* MyCollisionSphere;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	//Variables
	float SphereRaidus = 5.0f;

	//Functions
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool GetIsFilledWithLiquid();
	void SetIsFilledWithLiquid(bool Value);
	
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* Text;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* State;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* CapMesh;

	
	bool IsFilledWithLiquid = false;

	UPROPERTY()
	UScaleLerp* Liquid;

	UPROPERTY()
	AFoodContainer* FoodContainer;


public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* RootCollisionMesh;
	
	virtual void StartAction_Implementation() override;
	virtual void StopAction_Implementation() override;
};
