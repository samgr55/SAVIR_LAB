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

	SetUpInfo();
	
	WidgetComponent = Cast<UGeneralInfoWidgetComponent>(GetComponentByClass(UGeneralInfoWidgetComponent::StaticClass()));
	if(!WidgetComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Empty WidgetComponent in AInformationActor::BeginPlay"));
		return;
	}
	
	WidgetComponent->SetUpWidgetComponent();
	OriginalPosition = GetActorLocation();
	OriginalRotation = GetActorRotation().Quaternion();
}

void AInformationActor::SetUpInfo()
{
	if(!DataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Get DataTable in AInformationActor::SetUpInfo"));
		return;
	}
	DataRow = DataTable->FindRow<FGeneralInfoDT>(FName(FString::FromInt(RowID)), "");
	
	if(!DataRow)
	{
		UE_LOG(LogTemp, Error, TEXT("!DataRow in AInformationActor::SetUpInfo"));
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

void AInformationActor::ShowWidget()
{
	WidgetComponent->ShowWidget();
}

void AInformationActor::HideWidget()
{
	WidgetComponent->HideWidget();
}

UStaticMeshComponent* AInformationActor::GetStaticMeshComponent() const
{
	return StaticMeshComponent;
}


void AInformationActor::StartAction_Implementation()
{
	IAction::StartAction_Implementation();
	
}
	

void AInformationActor::StopAction_Implementation()
{
	IAction::StopAction_Implementation();
	
}
