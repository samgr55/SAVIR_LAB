// Fill out your copyright notice in the Description page of Project Settings.


#include "ChemicalMaterial/ChemicalContainer.h"

#include "ChemicalMaterial/ChemicalElement.h"
#include "Components/WidgetComponent.h"
#include "Engine/DataTable.h"

// Sets default values
AChemicalContainer::AChemicalContainer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = StaticMeshComp;
}


// Called when the game starts or when spawned
void AChemicalContainer::BeginPlay()
{
	Super::BeginPlay();

	OriginalPosition = GetActorLocation();
	OriginalRotation = GetActorRotation().Quaternion();
	OnActorHit.AddDynamic(this, &AChemicalContainer::OnHit);

	ChemicalElement = DataTable->FindRow<FChemicalElement>(FName(FString::FromInt(SubstanceID)), "");
	Description = ChemicalElement->Description;
	ImageDescription = NewObject<UImage>(GetWorld());
	//ImageDescription->SetBrushFromTexture(ChemicalElement->Image);
	ImageDescription = ChemicalElement->Image;
	
}

// Called every frame
void AChemicalContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AChemicalContainer::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OriginalParent)
	{
		UE_LOG(LogTemp, Warning, TEXT("HIT other"));
		OriginalParent = OtherActor;
	}
	//if the other actor isn't self or owner and exists then applay damage.
	if (!CurrentParent && OtherActor != OriginalParent)
	{
		UE_LOG(LogTemp, Warning, TEXT("other"));
		//SetActorLocation(OriginalPosition,false,nullptr,ETeleportType::TeleportPhysics);
		SetActorLocationAndRotation(OriginalPosition, OriginalRotation, false, nullptr, ETeleportType::TeleportPhysics);
	}
}
