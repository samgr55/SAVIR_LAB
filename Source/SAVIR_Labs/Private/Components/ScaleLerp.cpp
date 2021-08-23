// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ScaleLerp.h"

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

	Circle = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()->GetChildComponent(0));

	if (!Circle)
	{
		UE_LOG(LogTemp, Error, TEXT("Not Found Child static mesh"));
		return;
	}

	CurrentScale = Circle->GetRelativeScale3D();
	BeginScale = CurrentScale;
	//EndScale += CurrentScale;
}


// Called every frame
void UScaleLerp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
	ScaleCircle(DeltaTime);
}

void UScaleLerp::ScaleCircle(float DeltaTime)
{

	if(WaitTime > 0)
	{
		WaitTime -= DeltaTime;
		return;
	}
	
	if(TimeElapsed < LerpDuration)
	{
		CurrentScale = FMath::Lerp(CurrentScale, EndScale,  (TimeElapsed/LerpDuration));

		Circle->SetRelativeScale3D(CurrentScale);

		TimeElapsed += DeltaTime;
	}
	

	// if ((Circle->GetRelativeScale3D().X == EndScale.X) && (Circle->GetRelativeScale3D().Y == EndScale.Y))
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("Scale is Equal"));
	// }
}

void UScaleLerp::MinimizeCircle(float DeltaTime)
{
	if(TimeElapsed < LerpDuration)
	{
		CurrentScale = FMath::Lerp(EndScale, BeginScale,  (TimeElapsed/LerpDuration));

		Circle->SetRelativeScale3D(CurrentScale);
		
		TimeElapsed += DeltaTime;
	}
}