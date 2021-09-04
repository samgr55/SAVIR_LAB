// Fill out your copyright notice in the Description page of Project Settings.


#include "General/InformationActor.h"

#include "GeneralInfoDT.h"
#include "Components/Image.h"
#include "Components/WidgetComponent.h"
#include "Engine/DataTable.h"
#include "Widgets/GeneralInfoWidgetComponent.h"


// Sets default values
AInformationActor::AInformationActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;
	Description = "";
	ImageDescription = nullptr;
	bCanBeGrabbed = false;
	bIsGrabbedWithHand = true;
	bIsShowingInfoWidget = false;
	bIsInAction = false;

	InformationActorRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("IARootComponent"));
	InformationActorRootComponent->SetVisibility(true, true);
	RootComponent = InformationActorRootComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainStaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}


// Called when the game starts or when spawned
void AInformationActor::BeginPlay()
{
	Super::BeginPlay();

	OriginalPosition = GetActorLocation();
	OriginalRotation = GetActorRotation().Quaternion();

	SetUpInfo();

	WidgetComponent = Cast<
		UGeneralInfoWidgetComponent>(GetComponentByClass(UGeneralInfoWidgetComponent::StaticClass()));
	if (!WidgetComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Empty WidgetComponent in AInformationActor::BeginPlay"));
		return;
	}

	WidgetComponent->SetUpWidgetComponent();
}

void AInformationActor::SetUpInfo()
{
	if (!DataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Get DataTable in AInformationActor::SetUpInfo in: %s"), *GetName());
		return;
	}
	DataRow = DataTable->FindRow<FGeneralInfoDT>(FName(FString::FromInt(RowID)), "");

	if (!DataRow)
	{
		UE_LOG(LogTemp, Error, TEXT("!DataRow in AInformationActor::SetUpInfo in: "), *GetName());
		return;
	}
	Description = DataRow->Description;
	ImageDescription = NewObject<UImage>(this);
	ImageDescription->SetBrushFromMaterial(DataRow->Image);
	//ImageDescription = DataRow->Image;
}

void AInformationActor::ResetToOriginalPosition()
{
	SetActorLocationAndRotation(OriginalPosition, OriginalRotation, false, nullptr, ETeleportType::ResetPhysics);
}

bool AInformationActor::IsIsInAction() const
{
	return bIsInAction;
}

// Called every frame
void AInformationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FString AInformationActor::GetDescription_Implementation()
{
	return Description;
}

UImage* AInformationActor::GetImageDescription_Implementation()
{
	return ImageDescription;
}

bool AInformationActor::IsShowingInfoWidget()
{
	return bIsShowingInfoWidget;
}

void AInformationActor::ShowWidget()
{
	bIsShowingInfoWidget = true;
	WidgetComponent->ShowWidget();
}

void AInformationActor::HideWidget()
{
	bIsShowingInfoWidget = false;
	WidgetComponent->HideWidget();
}

void AInformationActor::StartAction_Implementation()
{
	IAction::StartAction_Implementation();
	bIsInAction = true;
}


void AInformationActor::StopAction_Implementation()
{
	IAction::StopAction_Implementation();
	bIsInAction = false;
}
