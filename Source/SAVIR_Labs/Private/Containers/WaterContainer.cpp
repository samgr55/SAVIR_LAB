// Fill out your copyright notice in the Description page of Project Settings.


#include "Containers/WaterContainer.h"

#include "Components/TextRenderComponent.h"

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

	Text = Cast<UTextRenderComponent>(GetComponentByClass(UTextRenderComponent::StaticClass()));
	if (!Text)
	{
		UE_LOG(LogTemp, Error, TEXT("Text Renderer not found"));
		return;
	}

	Text->SetText(FText::FromString((TEXT("Grab G"))));
}

// Called every frame
void AWaterContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentParent)
	{
		Text->SetText(FText::FromString((TEXT("Release R"))));
	}
	else
	{
		Text->SetText(FText::FromString((TEXT("Grab G"))));
	}
	
}

float AWaterContainer::GetTemperature()
{
	return Temperature;
}
