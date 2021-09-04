// Fill out your copyright notice in the Description page of Project Settings.


#include "General/OverlappingActors.h"

// Sets default values
AOverlappingActors::AOverlappingActors()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	
	LiquidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Liquid Mesh"));
	LiquidMesh->SetupAttachment(StaticMeshComponent);
}

// Called when the game starts or when spawned
void AOverlappingActors::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AOverlappingActors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

