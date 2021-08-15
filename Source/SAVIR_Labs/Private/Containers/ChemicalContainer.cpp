// Fill out your copyright notice in the Description page of Project Settings.


#include "Containers/ChemicalContainer.h"

#include "Components/WidgetComponent.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AChemicalContainer::AChemicalContainer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RowID = 1;
}


// Called when the game starts or when spawned
void AChemicalContainer::BeginPlay()
{
	UE_LOG(LogTemp, Error, TEXT("AChemicalContainer::BeginPlay"));
	Super::BeginPlay();
	OriginalPosition = GetActorLocation();
	OriginalRotation = GetActorRotation().Quaternion();

	
	SmokeParticle = Cast<UParticleSystemComponent>(GetComponentByClass(UParticleSystemComponent::StaticClass()));

	if (!SmokeParticle)
	{
		UE_LOG(LogTemp, Error, TEXT("Particle Not found"));
		return;
	}

	
	SmokeParticle->Deactivate();
	
	OnActorHit.AddDynamic(this, &AChemicalContainer::OnHit);

	
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
		UE_LOG(LogTemp, Error, TEXT("HIT other"));
		OriginalParent = OtherActor;
	}
	//if the other actor isn't self or owner and exists then applay damage.
	if (!CurrentParent && OtherActor != OriginalParent)
	{
		UE_LOG(LogTemp, Error, TEXT("other"));
		//SetActorLocation(OriginalPosition,false,nullptr,ETeleportType::TeleportPhysics);
		SetActorLocationAndRotation(OriginalPosition, OriginalRotation, false, nullptr, ETeleportType::TeleportPhysics);
	}
}


void AChemicalContainer::SpawnParticleSmoke()
{
	SmokeParticle->Activate(true);
}
