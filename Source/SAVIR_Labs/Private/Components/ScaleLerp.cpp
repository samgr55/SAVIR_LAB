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

	DoorTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimelineComp"));
}


// Called when the game starts
void UScaleLerp::BeginPlay()
{
	Super::BeginPlay();

	// ...

	Circle = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()->GetChildComponent(index));

	if (!Circle)
	{
		UE_LOG(LogTemp, Error, TEXT("Not Found Child static mesh"));
		return;
	}

	CurrentScale = Circle->GetRelativeScale3D();
	BeginScale = CurrentScale;
	//EndScale += CurrentScale;

	//Binding our float track to our UpdateTimelineComp Function's output
	UpdateFunctionFloat.BindUFunction(this, FName("UpdateFunctionFloat"));

	//If we have a float curve, bind it's graph to our update function
	if (DoorTimelineFloatCurve)
	{
		DoorTimelineComp->AddInterpVector(DoorTimelineFloatCurve, UpdateFunctionFloat);
	}
}


// Called every frame
void UScaleLerp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	// if(BeginScaleLerp)
	// {
	// 	MaxmizeScale(DeltaTime);
	// }
	if(BeginScaleLerp)
	{
		DoorTimelineComp->Play();
	}
}

void UScaleLerp::MaxmizeScale(float DeltaTime)
{
	// if (WaitTime > 0)
	// {
	// 	WaitTime -= DeltaTime;
	// 	return;
	// }

	if (TimeElapsed < LerpDuration)
	{
		//CurrentScale = FMath::Lerp(CurrentScale, EndScale, (TimeElapsed / LerpDuration));

		CurrentScale.X = FMath::Lerp(CurrentScale.X, EndScale.X, (TimeElapsed / LerpDuration));
		CurrentScale.Y = FMath::Lerp(CurrentScale.Y, EndScale.Y, (TimeElapsed / LerpDuration));
		CurrentScale.Z = FMath::Lerp(CurrentScale.Z, EndScale.Z, (TimeElapsed / LerpDuration));
		
		Circle->SetRelativeScale3D(CurrentScale);

		TimeElapsed += DeltaTime;

		UE_LOG(LogTemp,Error,TEXT("scale sucess %f"), Circle->GetComponentScale().X);
	
		// if(Circle->GetComponentScale().X >= EndScale.X)
		// {
		// 	UE_LOG(LogTemp,Error,TEXT("scale sucess %f"), Circle->GetComponentScale().X);
		// }

		//UE_LOG(LogTemp,Error,TEXT("Seconds : %f"), TimeElapsed);
	}


	// if ((Circle->GetRelativeScale3D().X == EndScale.X) && (Circle->GetRelativeScale3D().Y == EndScale.Y))
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("Scale is Equal"));
	// }
}

void UScaleLerp::MinimizeScale(float DeltaTime)
{
	if (TimeElapsed < LerpDuration)
	{
		CurrentScale = FMath::Lerp(EndScale, BeginScale, (TimeElapsed / LerpDuration));

		Circle->SetRelativeScale3D(CurrentScale);

		TimeElapsed += DeltaTime;

		
	}
}

void UScaleLerp::InitiateScale()
{
	BeginScaleLerp = true;
}

void UScaleLerp::UpdateTimelineComp(FVector endScal)
{
	// Create and set our Door's new relative location based on the output from our Timeline Curve
	FVector DoorNewRotation = endScal;
	Circle->SetRelativeScale3D(endScal);
}