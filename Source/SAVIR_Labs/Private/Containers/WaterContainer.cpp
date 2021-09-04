// Fill out your copyright notice in the Description page of Project Settings.


#include "Containers/WaterContainer.h"

// Sets default values
AWaterContainer::AWaterContainer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	InformationActorRootComponent->DestroyComponent();
	InformationActorRootComponent = nullptr;
	
	RootCollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("RootCollisionMesh"));
	//RootComponent = RootCollisionMesh;
	SetRootComponent(RootCollisionMesh);
	StaticMeshComponent->SetupAttachment(RootCollisionMesh);
	LiquidMesh->SetupAttachment(StaticMeshComponent);
}

// Called when the game starts or when spawned
void AWaterContainer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWaterContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AWaterContainer::GetTemperature()
{
	return Temperature;
}
