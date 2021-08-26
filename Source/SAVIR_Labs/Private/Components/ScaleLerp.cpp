// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ScaleLerp.h"

#include "Components/TimelineComponent.h"

// Sets default values for this component's properties
UScaleLerp::UScaleLerp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UScaleLerp::BeginPlay()
{
	Super::BeginPlay();

	// ...

	MeshToScale = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()->GetChildComponent(MeshIndex));

	if (!MeshToScale)
	{
		UE_LOG(LogTemp, Error, TEXT("Not Found Child static mesh"));
		return;
	}

	// if (CurveFloat)
	// {
	// 	FOnTimelineFloat TimelineProgress;
	// 	TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
	// 	CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
	// 	CurveTimeline.SetLooping(false);
	// }


	BeginScale = MeshToScale->GetRelativeScale3D();;
}


// Called every frame
void UScaleLerp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (bMaximizeScale)
	{
		MaximizeScale(DeltaTime);
	}
	else
	{
		MinimizeScale(DeltaTime);
	}

	if (bIsTimeline)
	{
		CurveTimeline.TickTimeline(DeltaTime);
	}
}

void UScaleLerp::MaximizeScale(float DeltaTime)
{
	if (TimeElapsed < LerpDuration)
	{
		FVector CurrentScale = FMath::Lerp(BeginScale, EndScale, (TimeElapsed / LerpDuration));

		MeshToScale->SetRelativeScale3D(CurrentScale);

		TimeElapsed += DeltaTime;
	}
}

void UScaleLerp::MinimizeScale(float DeltaTime)
{
	if (TimeElapsed < LerpDuration)
	{
		FVector CurrentScale = FMath::Lerp(EndScale, BeginScale, (TimeElapsed / LerpDuration));

		MeshToScale->SetRelativeScale3D(CurrentScale);

		TimeElapsed += DeltaTime;
	}
}

void UScaleLerp::InitiateMaxScale()
{
	bMaximizeScale = true;
	TimeElapsed = 0.0f;
}

void UScaleLerp::InitiateMinScale()
{
	bMaximizeScale = false;
	TimeElapsed = 0.0f;
}

void UScaleLerp::InitiateMaxScaleThermometer(FVector Value)
{
	bMaximizeThermometer = true;
	MeshToScale->SetRelativeScale3D(BeginScale);
	EndScale = Value;
}


void UScaleLerp::InitiateTimeline()
{
	bIsTimeline = true;
	CurveTimeline.PlayFromStart();
}

void UScaleLerp::SetTimeInSeconds(UCurveFloat* Value)
{
	CurveFloat = Value;

	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		CurveTimeline.SetLooping(false);
	}
}


void UScaleLerp::TimelineProgress(float Value)
{
	FVector CurrentScale = FMath::Lerp(BeginScale, EndScale, Value);

	MeshToScale->SetRelativeScale3D(CurrentScale);
}

void UScaleLerp::SetEndScale(FVector Value)
{
	EndScale = Value;
}
