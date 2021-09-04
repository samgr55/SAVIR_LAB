// Fill out your copyright notice in the Description page of Project Settings.


#include "Containers/Thermometer.h"

#include <string>

#include "Components/ScaleLerp.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "Containers/WaterContainer.h"

// Sets default values
AThermometer::AThermometer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootCollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("RootCollisionMesh"));
	RootComponent = RootCollisionMesh;
	InformationActorRootComponent->DestroyComponent(true);
	InformationActorRootComponent = nullptr;

	MyCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MyCollisionSphere->InitSphereRadius(SphereRaidus);
	MyCollisionSphere->SetCollisionProfileName("Trigger");
	MyCollisionSphere->SetupAttachment(StaticMeshComponent);

	bIsOverlappingWithWaterContainer = false;
}

// Called when the game starts or when spawned
void AThermometer::BeginPlay()
{
	Super::BeginPlay();

	MyCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AThermometer::OnOverlapBegin);
	MyCollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AThermometer::OnOverlapEnd);

	Text = Cast<UTextRenderComponent>(GetComponentByClass(UTextRenderComponent::StaticClass()));
	if (!Text)
	{
		UE_LOG(LogTemp, Error, TEXT("Text Renderer not found"));
		return;
	}

	Temperature = 0;
	Text->SetText(FText::FromString(FString::SanitizeFloat(Temperature)));
}

void AThermometer::StartAction_Implementation()
{
	Super::StartAction_Implementation();

	if(!WaterContainer)
	{
		UE_LOG(LogTemp, Error, TEXT("Not WaterContainer"));
		return;
	}
	Temperature = WaterContainer->GetTemperature();
	
	StaticMeshComponent->SetCollisionProfileName(FName("OverlapAll"));
	StaticMeshComponent->AttachToComponent(WaterContainer->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
	Text->SetText(FText::FromString(FString::SanitizeFloat(Temperature)));
}

void AThermometer::StopAction_Implementation()
{
	Super::StopAction_Implementation();
	//StaticMeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	StaticMeshComponent->SetCollisionProfileName(FName("BlockAll"));
}

// Called every frame
void AThermometer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AThermometer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if ((OtherActor = Cast<AWaterContainer>(OtherActor)) != nullptr)
		{
			WaterContainer = Cast<AWaterContainer>(OtherActor);
			
			auto Liquid = Cast<UScaleLerp>(GetComponentByClass(UScaleLerp::StaticClass()));

			if (!Liquid)
			{
				UE_LOG(LogTemp, Error, TEXT("Scale Lerp Not Found."));
	
			}
	
			bIsOverlappingWithWaterContainer = true;
			
			Text->SetText(FText::FromString("Press F to Measure"));
		}
	}
}

void AThermometer::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(Cast<AWaterContainer>(OtherActor))
	{
		bIsOverlappingWithWaterContainer = false;
		Text->SetText(FText::FromString(FString::SanitizeFloat(Temperature)));
	}
	else if(WaterContainer)
	{
		bIsOverlappingWithWaterContainer = false;
		Text->SetText(FText::FromString(FString::SanitizeFloat(Temperature)));
		WaterContainer = nullptr;
	}
}

float AThermometer::GetTemperature()
{
	return Temperature;
}

void AThermometer::SetTemperature(float temperature)
{
	Temperature = temperature;
}
