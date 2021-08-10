// Fill out your copyright notice in the Description page of Project Settings.


#include "ChemicalMaterial/ChemicalContainer.h"

#include "ChemicalInfoWidgets.h"
#include "ChemicalMaterial/ChemicalSubstance.h"

// Sets default values
AChemicalContainer::AChemicalContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = StaticMeshComp;
}

void AChemicalContainer::MoveTo(AChemicalContainer* NewContainer, bool bMoveAll, float MoveQuantity)
{
	if(!NewContainer) return;

	
	if(!NewContainer->Substance)
	{
		NewContainer->Substance = Substance;
	}
	else
	{
		if(!bMoveAll)
		{
			
			NewContainer->Substance->React(Substance);
		}	
	}

	if(bMoveAll)
	{
		Substance = nullptr;
	}
	
}

void AChemicalContainer::ShowWidget()
{
	WidgetComponent->GetWidget()->SetVisibility(ESlateVisibility::Visible);
}

void AChemicalContainer::HideWidget()
{
	WidgetComponent->GetWidget()->SetVisibility(ESlateVisibility::Collapsed);
}

// Called when the game starts or when spawned
void AChemicalContainer::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComp = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
	OriginalPosition = GetActorLocation();
	OriginalRotation = GetActorRotation().Quaternion();

	WidgetComponent = Cast<UWidgetComponent>(GetComponentByClass(UWidgetComponent::StaticClass()));
	if(WidgetComponent)
	{
		auto Widget = Cast<UChemicalInfoWidgets> (WidgetComponent->GetWidget());
		if(Widget)
		{
			if(!Substance)
			{
				UE_LOG(LogTemp, Error, TEXT("!Substance"));
			}
			if(!Substance->ChemicalElement)
			{
				UE_LOG(LogTemp, Error, TEXT("!Substance->ChemicalElement"));
			}
			Widget->SetUpWidget(Substance->ChemicalElement);
		}
	}
	OnActorHit.AddDynamic(this, &AChemicalContainer::OnHit);

	WidgetComponent->GetWidget()->SetVisibility(ESlateVisibility::Collapsed);
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