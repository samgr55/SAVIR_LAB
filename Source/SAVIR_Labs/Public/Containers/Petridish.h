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

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* SpotMesh;
	
	// Sets default values for this actor's properties
	APetridish();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

	virtual void StartAction_Implementation() override;
	virtual void StopAction_Implementation() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	
	UPROPERTY(VisibleAnywhere)
	USphereComponent* MyCollisionSphere;

	float SphereRaidus = 5.0f;

	float Temperature;

	bool isFilledWithLiquid = false;

	void SwitchCamera(AActor* Other);

	bool bUsedPetridish = false;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	AActor* CameraActor;
	
};
