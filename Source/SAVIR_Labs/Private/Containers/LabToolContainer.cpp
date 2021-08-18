// Fill out your copyright notice in the Description page of Project Settings.


#include "Containers/LabToolContainer.h"

// Sets default values
ALabToolContainer::ALabToolContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RowID = 1;
	bCanBeGrabbed = true;
}

// Called when the game starts or when spawned
void ALabToolContainer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALabToolContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
