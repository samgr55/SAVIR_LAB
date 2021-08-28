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

	MyCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MyCollisionSphere->InitSphereRadius(SphereRaidus);
	MyCollisionSphere->SetCollisionProfileName("Trigger");
	MyCollisionSphere->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AThermometer::BeginPlay()
{
	Super::BeginPlay();

	MyCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AThermometer::OnOverlapBegin);

	Text = Cast<UTextRenderComponent>(GetComponentByClass(UTextRenderComponent::StaticClass()));
	if (!Text)
	{
		UE_LOG(LogTemp, Error, TEXT("Text Renderer not found"));
		return;
	}

	//Text->SetText(FText::FromString(TEXT("20")));
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
			auto WaterContainer = Cast<AWaterContainer>(OtherActor);

			auto Liquid = Cast<UScaleLerp>(GetComponentByClass(UScaleLerp::StaticClass()));

			if (!Liquid)
			{
				UE_LOG(LogTemp, Error, TEXT("Scale Lerp Not Found."));
				return;
			}


			Temperature = WaterContainer->GetTemperature();

			if (Temperature == 5.0)
			{
				Text->SetText(FText::FromString(FString::SanitizeFloat(Temperature)));
			}
			else if (Temperature == 25)
			{
				Text->SetText(FText::FromString(FString::SanitizeFloat(Temperature)));
			}
			else if (Temperature == 50)
			{
				Text->SetText(FText::FromString(FString::SanitizeFloat(Temperature)));
			}
		}
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