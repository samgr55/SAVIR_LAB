#include "Components/Grabber.h"
#include "DrawDebugHelpers.h"
#include "PhysXInterfaceWrapperCore.h"
#include "Engine/World.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/PlayerController.h"
#include "Containers/ChemicalContainer.h"
#include "GameFramework/Character.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bIsHandGrabbing = false;
	bIsLineGrabbing = false;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	auto MeshComp = Cast<
		USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	if (!MeshComp)
	{
		UE_LOG(LogTemp, Error, TEXT("Faild to get MeshComponent in UGrabber::BeginPlay"));
		return;
	}

	LeftHandSocket = MeshComp->SkeletalMesh->FindSocket(FName("LeftHandSocket"));
	if (!LeftHandSocket)
	{
		UE_LOG(LogTemp, Error, TEXT("Faild to get LeftHandSocket in UGrabber::BeginPlay"));
		return;
	}

	RightHandSocket = MeshComp->SkeletalMesh->FindSocket(FName("RightHandSocket"));
	if (!RightHandSocket)
	{
		UE_LOG(LogTemp, Error, TEXT("Faild to get RightHandSocket in UGrabber::BeginPlay"));
		return;
	}

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("Faild to get OwnerCharactr in UGrabber::BeginPlay"));
		return;
	}

	SetupInputComponent();
}

void UGrabber::SetupInputComponent()
{
	auto InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Release", IE_Pressed, this, &UGrabber::Release);
		InputComponent->BindAction("ShowData", IE_Pressed, this, &UGrabber::ShowData);
		InputComponent->BindAction("ShowData", IE_Released, this, &UGrabber::HideData);
		InputComponent->BindAction("Action", IE_Pressed, this, &UGrabber::Action);
	}
}


void UGrabber::Grab()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	AActor* ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		auto InfoActor = Cast<AInformationActor>(HitResult.GetActor()); 
		if (InfoActor && InfoActor->bCanBeGrabbed)
		{
			if (InfoActor->bIsGrabbedWithHand && !HandGrabbedActor)
			{
				HandGrabbedActor = InfoActor;
				GrabWithHand();
			}
			else if(!InfoActor->bIsGrabbedWithHand && !LineGrabbedActor)
			{
				LineGrabbedActor = InfoActor;
				GrabWithLine();
			}
		}
		else if(InfoActor)
		{
			ActionGrabbed = InfoActor;
			ActionGrabbed->CurrentParent = GetOwner();
		}
	}
}

void UGrabber::Release()
{
	if (bIsHandGrabbing && HandGrabbedActor && !bIsLineGrabbing)
	{
		if(HandGrabbedActor->IsIsInAction())
		{
			StopHandAction();
		}
		HandGrabbedActor->SetRootComponent(HandGrabbedRoot);
		HandGrabbedActor->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
		HandGrabbedActor->ResetToOriginalPosition();
		HandGrabbedActor->StaticMeshComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
		HandGrabbedActor->CurrentParent = nullptr;
		HandGrabbedRoot = nullptr;
		HandGrabbedActor = nullptr;
		bIsHandGrabbing = false;
	}
	
	if(bIsLineGrabbing && LineGrabbedActor)
	{
		if(LineGrabbedActor->IsIsInAction())
		{
			StopLineAction();
		}
		LineGrabbedActor->ResetToOriginalPosition();
		bIsLineGrabbing = false;
		LineGrabbedActor->CurrentParent = nullptr;
		LineGrabbedActor = nullptr;
	}

	if(ActionGrabbed)
	{
		if(ActionGrabbed->IsIsInAction())
		{
			ActionGrabbed->StopAction_Implementation();
		}
		ActionGrabbed = nullptr;
	}

}


void UGrabber::ShowData()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	AActor* ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		auto InformationActor = Cast<AInformationActor>(HitResult.GetActor());
		if (InformationActor)
		{
			if (!InformationActor->IsShowingInfoWidget())
			{
				InformationActor->ShowWidget();
			}
			// else
			// {
			// 	InformationActor->HideWidget();
			// }
		}
	}
}

void UGrabber::HideData()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	AActor* ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		auto InformationActor = Cast<AInformationActor>(HitResult.GetActor());
		if (InformationActor)
		{
			if (InformationActor->IsShowingInfoWidget())
			{
				InformationActor->HideWidget();
			}
		}
	}
}

void UGrabber::GrabWithHand()
{
	bIsHandGrabbing = true;
	HandGrabbedActor->CurrentParent = GetOwner();
	if (!GetOwner()->GetRootComponent())
	{
		UE_LOG(LogTemp, Error, TEXT("Faild to get GetRootComponent in UGrabber::Grab"));
		return;
	}
	HandGrabbedActor->StaticMeshComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	HandGrabbedActor->AttachToActor(OwnerCharacter,
									FAttachmentTransformRules::SnapToTargetNotIncludingScale,
									FName("RightHandSocket"));
	HandGrabbedRoot = HandGrabbedActor->GetRootComponent();
	if (!HandGrabbedRoot)
	{
		UE_LOG(LogTemp, Error, TEXT("Faild to get GrabbedContainer StaticMeshComponent in UGrabber::Grab"));
		return;
	}
	auto SkeletalMesh = Cast<USkeletalMeshComponent>(
		GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	if (!SkeletalMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("Faild to get SkeletalMesh in UGrabber::Grab"));
		return;
	}

	SkeletalMesh->SetCollisionProfileName(TEXT("OverlapAll"));


	if (!HandGrabbedRoot->AttachToComponent(SkeletalMesh,
										FAttachmentTransformRules::SnapToTargetNotIncludingScale,
										FName("RightHandSocket")))
	{
		UE_LOG(LogTemp, Error, TEXT("Faild to AttachToComponent in UGrabber::Grab"));
		return;
	}
}

void UGrabber::GrabWithLine()
{
	bIsLineGrabbing = true;
	LineGrabbedActor->CurrentParent = GetOwner();
}

void UGrabber::Action()
{
	if (HandGrabbedActor && HandGrabbedActor->IsIsInAction())
	{
		StopHandAction();
	}
	else if (bIsHandGrabbing)
	{
		StartHandAction();
	}
	
	if(LineGrabbedActor && LineGrabbedActor->IsIsInAction())
	{
		StopLineAction();
	}
	else if (bIsLineGrabbing)
	{
		StartLineAction();
	}

	if(ActionGrabbed && ActionGrabbed->IsIsInAction())
	{
		ActionGrabbed->StopAction_Implementation();
	}
	else if(ActionGrabbed)
	{
		ActionGrabbed->StartAction_Implementation();
	}
}

void UGrabber::StartHandAction()
{
	if (!HandGrabbedActor)
	{
		return;
	}
	HandGrabbedActor->StartAction_Implementation();
}

void UGrabber::StartLineAction()
{
	if (!LineGrabbedActor)
	{
		return;
	}
	LineGrabbedActor->StartAction_Implementation();
}

void UGrabber::StopHandAction()
{
	if (!HandGrabbedActor)
	{
		return;
	}
	HandGrabbedActor->StopAction_Implementation();
}

void UGrabber::StopLineAction()
{
	if (!LineGrabbedActor)
	{
		return;
	}
	LineGrabbedActor->StopAction_Implementation();
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
	
	
	if (LineGrabbedActor && !LineGrabbedActor->bIsGrabbedWithHand && bIsLineGrabbing)
	{
		LineGrabbedActor->SetActorLocation(GetPlayerReach());
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

	UE_LOG(LogTemp, Warning, TEXT("Hit %d"), s);

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
