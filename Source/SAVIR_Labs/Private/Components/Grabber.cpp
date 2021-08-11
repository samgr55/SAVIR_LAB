#include "Components/Grabber.h"
#include "DrawDebugHelpers.h"
#include "PhysXInterfaceWrapperCore.h"
#include "Engine/World.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/PlayerController.h"
#include "SAVIR_Labs/Public/ChemicalMaterial/ChemicalContainer.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	SetupInputComponent();
}

void UGrabber::Grab()
{
	
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	AActor* ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
	    Continer =  Cast<AChemicalContainer>(HitResult.GetActor());
		if(Continer)
		{
			bIsGrabbed = true;
			Continer->CurrentParent = GetOwner();
		}
	}
}

void UGrabber::Release()
{
	bIsGrabbed = false;
	Continer->CurrentParent = nullptr;
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input Component found on %s"), *GetOwner()->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Release", IE_Pressed, this, &UGrabber::Release);
		InputComponent->BindAction("ShowData",IE_Pressed,this,&UGrabber::ShowData);
	}
}

void UGrabber::ShowData()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	AActor* ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		ShowWidgetData =  Cast<AChemicalContainer>(HitResult.GetActor());
		if(ShowWidgetData)
		{
			if(!bIsShowingData)
			{
				bIsShowingData = true;
				ShowWidgetData->ShowWidget();
			}
			else
			{
				bIsShowingData = false;
				ShowWidgetData->HideWidget();
			}
		}
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrawDebugLine(
		GetWorld(),
		GetPlayerWorldPos(),
		GetPlayerReach(),
		FColor(0.0f, 255, 0.0f),
		false,
		0.0f,
		0,
		5.0f
	);

	if(Continer && bIsGrabbed)
	{
		Continer->SetActorLocation(GetPlayerReach());
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	FHitResult Hit;

	//FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	FCollisionQueryParams TraceParams;

	bool s = GetWorld()->LineTraceSingleByChannel(OUT Hit,
		GetPlayerWorldPos(),
		GetPlayerReach(),
		ECC_Visibility,
		TraceParams);
	 

	UE_LOG(LogTemp,Warning,TEXT("Hit %d"),s);
	
	return Hit;
}

FVector UGrabber::GetPlayerWorldPos() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation;
}

FVector UGrabber::GetPlayerReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}