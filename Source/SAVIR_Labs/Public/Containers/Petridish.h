// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "General/OverlappingActors.h"

#include "Petridish.generated.h"

class USphereComponent;
UCLASS()
class SAVIR_LABS_API APetridish : public AOverlappingActors
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Timeline")
	UCurveFloat* CurveFloat_1;

	UPROPERTY(EditAnywhere, Category="Timeline")
	UCurveFloat* CurveFloat_2;

	UPROPERTY(EditAnywhere, Category="Timeline")
	UCurveFloat* CurveFloat_3;
	
	// Sets default values for this actor's properties
	APetridish();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SpotMesh;
	
	UPROPERTY(VisibleAnywhere)
	USphereComponent* MyCollisionSphere;

	float SphereRaidus = 5.0f;

	float Temperature;

	bool isFilledWithLiquid = false;

	bool bUsedPetridish = false;
};
