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

	//Functions
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void MaximizeScale(float DeltaTime);
	void MinimizeScale(float DeltaTime);

	void InitiateMaxScale();
	void InitiateMinScale();

	void InitiateMaxScaleThermometer(FVector Value);

	void InitiateTimeline();

	void SetTimeInSeconds(UCurveFloat* Value);
	void SetEndScale(FVector Value);

	void FastForwardScale(FVector endScale);


	UFUNCTION()
	void TimelineProgress(float Value);

protected:
	//Variables
	FTimeline CurveTimeline;

	UCurveFloat* CurveFloat;

	//Functions
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//Variables
	UPROPERTY()
	UStaticMeshComponent* MeshToScale;

	float TimeElapsed = 0;

	bool bIsTimeline = false;

	bool bMaximizeScale = false;

	bool bMaximizeThermometer = false;

	FVector BeginScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data", meta = (AllowPrivateAccess = "true"))
	FVector EndScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data", meta = (AllowPrivateAccess = "true"))
	float LerpDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data", meta = (AllowPrivateAccess = "true"))
	float WaitTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data", meta = (AllowPrivateAccess = "true"))
	int32 MeshIndex = 0;
};
