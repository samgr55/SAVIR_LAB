// Fill out your copyright notice in the Description page of Project Settings.


#include "Containers/Petridish.h"

#include "Components/ScaleLerp.h"
#include "Components/SphereComponent.h"
#include "Containers/Thermometer.h"

// Sets default values
APetridish::APetridish()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	LiquidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Liquid Mesh"));
	LiquidMesh->SetupAttachment(BaseMesh);

	SpotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spot Mesh"));
	SpotMesh->SetupAttachment(BaseMesh);

	MyCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MyCollisionSphere->InitSphereRadius(SphereRaidus);
	MyCollisionSphere->SetCollisionProfileName("Trigger");
	MyCollisionSphere->SetupAttachment(BaseMesh);
}

// Called when the game starts or when spawned
void APetridish::BeginPlay()
{
	Super::BeginPlay();
	MyCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APetridish::OnOverlapBegin);

	LiquidMesh->SetVisibility(false);
}

// Called every frame
void APetridish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APetridish::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if ((OtherActor = Cast<AThermometer>(OtherActor)) != nullptr)
		{	
			auto Liquid = Cast<UScaleLerp>(GetComponentByClass(UScaleLerp::StaticClass()));

			LiquidMesh->SetVisibility(true);
			if (!Liquid)
			{
				UE_LOG(LogTemp, Error, TEXT("Scale Lerp Not Found."));
				return;
			}

			Liquid->InitiateTimeline();
		}
	}
}
