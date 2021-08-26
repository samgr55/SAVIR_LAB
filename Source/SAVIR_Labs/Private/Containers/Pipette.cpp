// Fill out your copyright notice in the Description page of Project Settings.


#include "Containers/Pipette.h"

#include "Components/ScaleLerp.h"
#include "Components/SphereComponent.h"
#include "Containers/FoodContainer.h"
#include "Containers/Petridish.h"

// Sets default values
APipette::APipette()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cap Mesh"));
	CapMesh->SetupAttachment(BaseMesh);

	MyCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MyCollisionSphere->InitSphereRadius(SphereRaidus);
	MyCollisionSphere->SetCollisionProfileName("Trigger");
	MyCollisionSphere->SetupAttachment(BaseMesh);
}

// Called when the game starts or when spawned
void APipette::BeginPlay()
{
	Super::BeginPlay();

	MyCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APipette::OnOverlapBegin);
}

// Called every frame
void APipette::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void APipette::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (Cast<AFoodContainer>(OtherActor))
		{
			UScaleLerp* Liquid = Cast<UScaleLerp>(GetComponentByClass(UScaleLerp::StaticClass()));

			if (!Liquid)
			{
				UE_LOG(LogTemp, Error, TEXT("Scale Lerp Not Found."));
				return;
			}

			if (!IsFilledWithLiquid)
			{
				Liquid->InitiateMaxScale();
				IsFilledWithLiquid = true;
			}
		}
	}
}

bool APipette::GetIsFilledWithLiquid()
{
	return IsFilledWithLiquid;
}

void APipette::SetIsFilledWithLiquid(bool Value)
{
	IsFilledWithLiquid = Value;
}
