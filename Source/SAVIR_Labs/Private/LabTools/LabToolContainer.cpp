// Fill out your copyright notice in the Description page of Project Settings.


#include "LabTools/LabToolContainer.h"

// Sets default values
ALabToolContainer::ALabToolContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALabToolContainer::BeginPlay()
{
	Super::BeginPlay();

	OriginalPosition = GetActorLocation();
	OriginalRotation = GetActorRotation().Quaternion();

	OnActorHit.AddDynamic(this, &ALabToolContainer::OnHit);
	
}

// Called every frame
void ALabToolContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALabToolContainer::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
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