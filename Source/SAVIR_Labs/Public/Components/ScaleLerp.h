// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"

#include "ScaleLerp.generated.h"


class UTimelineComponent;
class FOnTimelineFloat;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SAVIR_LABS_API UScaleLerp : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UScaleLerp();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void MaxmizeScale(float DeltaTime);

	void MinimizeScale(float DeltaTime);

	void InitiateScale();
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* DoorTimelineComp;
	
	UPROPERTY(EditAnywhere)
	UCurveVector* DoorTimelineFloatCurve;

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//Variables
	UPROPERTY()
	UStaticMeshComponent* Circle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector EndScale = FVector(1, 1, 1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float LerpDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float WaitTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 index = 0;

	float TimeElapsed = 0;

	FVector CurrentScale;
	FVector BeginScale;

	bool BeginScaleLerp = false;

	//Float Track Signature to handle our update track event
	FOnTimelineVector UpdateFunctionFloat;

	UFUNCTION()
	void UpdateTimelineComp(FVector endScal);
};
