// Fill out your copyright notice in the Description page of Project Settings.


#include "Containers/Petridish.h"

#include "Components/ScaleLerp.h"
#include "Components/SphereComponent.h"
#include "Containers/Pipette.h"
#include "Containers/WaterContainer.h"

// Sets default values
APetridish::APetridish()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spot Mesh"));
	SpotMesh->SetupAttachment(RootComponent);

	MyCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MyCollisionSphere->InitSphereRadius(SphereRaidus);
	MyCollisionSphere->SetCollisionProfileName("Trigger");
	MyCollisionSphere->SetupAttachment(RootComponent);
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
		if (Cast<APipette>(OtherActor))
		{
			auto Liquid = Cast<UScaleLerp>(GetComponentByClass(UScaleLerp::StaticClass()));

			if (!Liquid)
			{
				UE_LOG(LogTemp, Error, TEXT("Scale Lerp Not Found."));
				return;
			}

			auto Pipette = Cast<APipette>(OtherActor);

			if(!Pipette)
			{
				UE_LOG(LogTemp, Error, TEXT("Pipette Not Found."));
				return;
			}

			if (isFilledWithLiquid && Pipette->GetIsFilledWithLiquid() && !bUsedPetridish)
			{
				bUsedPetridish = true;
				Pipette->SetIsFilledWithLiquid(false);

				Cast<UScaleLerp>(Pipette->GetComponentByClass(UScaleLerp::StaticClass()))->InitiateMinScale();

				if (Temperature == 50)
				{
					Liquid->SetTimeInSeconds(CurveFloat_3);
					Liquid->SetEndScale(FVector(0.058, 0.058, 0.002));
					Liquid->InitiateTimeline();
				}
				else if (Temperature == 25)
				{
					Liquid->SetTimeInSeconds(CurveFloat_2);
					Liquid->SetEndScale(FVector(0.034, 0.034, 0.002));
					Liquid->InitiateTimeline();
				}
				else if (Temperature == 5)
				{
					Liquid->SetTimeInSeconds(CurveFloat_1);
					Liquid->SetEndScale(FVector(0.02, 0.02, 0.002));
					Liquid->InitiateTimeline();
				}
			}
		}
		else if (Cast<AWaterContainer>(OtherActor))
		{
			if(!isFilledWithLiquid)
			{
				LiquidMesh->SetVisibility(true);
				isFilledWithLiquid = true;
				Temperature = Cast<AWaterContainer>(OtherActor)->GetTemperature();
			}
		}
	}
}