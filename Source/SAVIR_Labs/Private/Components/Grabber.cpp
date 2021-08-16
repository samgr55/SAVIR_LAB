#include "Components/Grabber.h"
#include "DrawDebugHelpers.h"
#include "PhysXInterfaceWrapperCore.h"
#include "Engine/World.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/PlayerController.h"
#include "Containers/ChemicalContainer.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bIsAction = false;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	auto MeshComp = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	if(!MeshComp)
	{
		UE_LOG(LogTemp, Error, TEXT("Faild to get MeshComponent in UGrabber::BeginPlay"));
		return;
	}

	LeftHandSocket = MeshComp->SkeletalMesh->FindSocket(FName("LeftHandSocket"));
	if(!LeftHandSocket)
	{
		UE_LOG(LogTemp, Error, TEXT("Faild to get LeftHandSocket in UGrabber::BeginPlay"));
		return;
	}
	
	RightHandSocket = MeshComp->SkeletalMesh->FindSocket(FName("RightHandSocket"));
	if(!RightHandSocket)
	{
		UE_LOG(LogTemp, Error, TEXT("Faild to get RightHandSocket in UGrabber::BeginPlay"));
		return;
	}

	SetupInputComponent();
}

void UGrabber::Grab()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	AActor* ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		GrabbedContainer = Cast<AChemicalContainer>(HitResult.GetActor());
		if (GrabbedContainer)
		{
			bIsGrabbed = true;
			GrabbedContainer->CurrentParent = GetOwner();
			GrabbedContainer->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RightHandSocket"));
		}
	}
}

void UGrabber::Release()
{
	if (!bIsGrabbed)
	{
		return; 
	}
	if(bIsAction)
	{
		StopAction();
	}
	bIsGrabbed = false;
	GrabbedContainer->AttachToActor(GrabbedContainer, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	GrabbedContainer->CurrentParent = nullptr;
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Input Component found on %s"), *GetOwner()->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Release", IE_Pressed, this, &UGrabber::Release);
		InputComponent->BindAction("ShowData", IE_Pressed, this, &UGrabber::ShowData);
		InputComponent->BindAction("Action", IE_Pressed, this, &UGrabber::Action);
	}
}

void UGrabber::ShowData()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	AActor* ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		InformationActor = Cast<AInformationActor>(HitResult.GetActor());
		if (InformationActor)
		{
			if (!bIsShowingData)
			{
				bIsShowingData = true;
				InformationActor->ShowWidget();
			}
			else
			{
				bIsShowingData = false;
				InformationActor->HideWidget();
			}
		}
	}
}

void UGrabber::Action()
{
	if(bIsAction)
	{
		StopAction();
		bIsAction = false;
	}
	else if(bIsGrabbed)
	{
		StartAction();
		bIsAction = true;
	}
}

void UGrabber::StartAction()
{
	GrabbedContainer->StartAction_Implementation();
}

void UGrabber::StopAction()
{
	GrabbedContainer->StopAction_Implementation();
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
	
	
	/*if (GrabbedContainer && bIsGrabbed)
	{
		GrabbedContainer->SetActorLocation(GetPlayerReach());
	}*/
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


	UE_LOG(LogTemp, Error, TEXT("Hit %d"), s);

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
