// Fill out your copyright notice in the Description page of Project Settings.


#include "General/InformationActor.h"


// Sets default values
AInformationActor::AInformationActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Description = "";
	ImageDescription = nullptr;
}

// Called when the game starts or when spawned
void AInformationActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInformationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FString AInformationActor::GetDescription_Implementation()
{
	return Description;
}

UImage* AInformationActor::GetImageDescription_Implementation()
{
	return ImageDescription;
}

