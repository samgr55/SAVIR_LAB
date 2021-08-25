// Fill out your copyright notice in the Description page of Project Settings.


#include "Containers/FoodContainer.h"

#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"

// Sets default values
AFoodContainer::AFoodContainer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	CapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cap Mesh"));
	CapMesh->SetupAttachment(BaseMesh);

	LiquidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Liquid Mesh"));
	LiquidMesh->SetupAttachment(BaseMesh);
}

// Called when the game starts or when spawned
void AFoodContainer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFoodContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRaidus, 20, FColor::Purple, false, -1, 0, 1);
}

void AFoodContainer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		
	}
}
