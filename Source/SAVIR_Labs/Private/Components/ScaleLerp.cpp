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

	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		CurveTimeline.SetLooping(false);
	}


	BeginScale = MeshToScale->GetRelativeScale3D();;
	//EndScale += CurrentScale;
}


// Called every frame
void UScaleLerp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (BeginScaleLerp)
	{
		MaximizeScale(DeltaTime);
	}

	if (TimeLineLerp)
	{
		CurveTimeline.TickTimeline(DeltaTime);
	}
}

void UScaleLerp::MaximizeScale(float DeltaTime)
{
	// if (WaitTime > 0)
	// {
	// 	WaitTime -= DeltaTime;
	// 	return;
	// }

	if (TimeElapsed < LerpDuration)
	{
		FVector CurrentScale = FMath::Lerp(BeginScale, EndScale, (TimeElapsed / LerpDuration));

		MeshToScale->SetRelativeScale3D(CurrentScale);

		TimeElapsed += DeltaTime;

		UE_LOG(LogTemp, Error, TEXT("scale sucess %f"), MeshToScale->GetComponentScale().X);
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

void UScaleLerp::InitiateScale()
{
	BeginScaleLerp = true;
}

void UScaleLerp::InitiateTimeline()
{
	UE_LOG(LogTemp, Error, TEXT("Timeline"));
	TimeLineLerp = true;
	CurveTimeline.PlayFromStart();
}

void UScaleLerp::TimelineProgress(float Value)
{
	FVector CurrentScale = FMath::Lerp(BeginScale, EndScale, Value);

	MeshToScale->SetRelativeScale3D(CurrentScale);
}
