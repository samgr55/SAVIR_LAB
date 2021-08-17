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
	bCanBeGrabbed = true;
}

void AChemicalContainer::StartAction_Implementation()
{
	Super::StartAction_Implementation();
	/*
	if(!CapMesh)
	{
	UE_LOG(LogTemp, Error, TEXT("CapMesh Not found in AChemicalContainer::StartAction_Implementation"));
	return;
	}
	if(!CurrentParent)
	{
	UE_LOG(LogTemp, Error, TEXT("CurrentParent Not found in AChemicalContainer::StartAction_Implementation"));
	return;
	}

	StaticMeshComponent->AttachToComponent(Cast<USkeletalMeshComponent>(
	CurrentParent->GetComponentByClass(USkeletalMeshComponent::StaticClass())),
	FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RightHandSocket"));
	CapMesh->AttachToComponent(Cast<USkeletalMeshComponent>(
	CurrentParent->GetComponentByClass(USkeletalMeshComponent::StaticClass())),
	FAttachmentTransformRules::SnapToTargetNotIncludingScale, "LeftHandSocket");
	*/
	
	SmokeParticle->SetVisibility(true, true);
}

void AChemicalContainer::StopAction_Implementation()
{
	Super::StopAction_Implementation();
	SmokeParticle->SetVisibility(false, true);
	/*
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	CapMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	*/
	
}


// Called when the game starts or when spawned
void AChemicalContainer::BeginPlay()
{
	Super::BeginPlay();
	OriginalPosition = GetActorLocation();
	OriginalRotation = GetActorRotation().Quaternion();
	OnActorHit.AddDynamic(this, &AChemicalContainer::OnHit);

	SmokeParticle = Cast<UParticleSystemComponent>(GetComponentByClass(UParticleSystemComponent::StaticClass()));
	
	if (!SmokeParticle)
	{
		UE_LOG(LogTemp, Error, TEXT("Particle Not found in AChemicalContainer::BeginPlay"));
		return;
	}
	SmokeParticle->SetVisibility(false, true);
	OnActorHit.AddDynamic(this, &AChemicalContainer::OnHit);

	CapMesh = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(FName("Cap")));

	if(!CapMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("CapMesh Not found in AChemicalContainer::BeginPlay"));
		return;
	}
	
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
		OriginalParent = OtherActor;
	}
	//if the other actor isn't self or owner and exists then applay damage.
	if (!CurrentParent && OtherActor != OriginalParent)
	{
		//SetActorLocation(OriginalPosition,false,nullptr,ETeleportType::TeleportPhysics);
		SetActorLocationAndRotation(OriginalPosition, OriginalRotation, false, nullptr, ETeleportType::ResetPhysics);
	}
}


void AChemicalContainer::SpawnParticleSmoke()
{
	SmokeParticle->Activate(true);
}
