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
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshZizo");
	RootComponent = StaticMeshComp;
	
	
	
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
}

void AInformationActor::SetUpInfo()
{
	DataRow = DataTable->FindRow<FGeneralInfoDT>(FName(FString::FromInt(RowID)), "");
	
	if(!DataRow)
	{
		UE_LOG(LogTemp, Error, TEXT("!DataRow in AInformationActor::BeginPlay"));
		return;
	}
	Description = DataRow->Description;
	ImageDescription = NewObject<UImage>(this);
	ImageDescription->SetBrushFromTexture(DataRow->Image);
	//ImageDescription = DataRow->Image;
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

