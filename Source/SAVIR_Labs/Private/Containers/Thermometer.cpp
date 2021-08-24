// Fill out your copyright notice in the Description page of Project Settings.


#include "Containers/Thermometer.h"

#include "Components/ScaleLerp.h"
#include "Components/SphereComponent.h"
#include "Containers/WaterContainer.h"

// Sets default values
AThermometer::AThermometer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	LiquidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Liquid Mesh"));
	LiquidMesh->SetupAttachment(BaseMesh);

	MyCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MyCollisionSphere->InitSphereRadius(SphereRaidus);
	MyCollisionSphere->SetCollisionProfileName("Trigger");
	MyCollisionSphere->SetupAttachment(BaseMesh);
}

// Called when the game starts or when spawned
void AThermometer::BeginPlay()
{
	Super::BeginPlay();

	MyCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AThermometer::OnOverlapBegin);
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
			auto WaterContiner = Cast<AWaterContainer>(OtherActor);
			
			auto Liquid = Cast<UScaleLerp>(GetComponentByClass(UScaleLerp::StaticClass()));

			if (!Liquid)
			{
				UE_LOG(LogTemp, Error, TEXT("Scale Lerp Not Found."));
				return;
			}

			
			Temperature = WaterContiner->GetTemperature();

			UE_LOG(LogTemp, Error, TEXT("Tempe %f"), Temperature);

			Liquid->InitiateScale();
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
