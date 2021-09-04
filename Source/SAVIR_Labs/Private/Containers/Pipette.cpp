// Fill out your copyright notice in the Description page of Project Settings.


#include "Containers/Pipette.h"

#include "Components/ScaleLerp.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "Containers/FoodContainer.h"
#include "Containers/Petridish.h"

// Sets default values
APipette::APipette()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InformationActorRootComponent->DestroyComponent();
	InformationActorRootComponent = nullptr;

	RootCollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("RootCollisionMesh"));

	SetRootComponent(RootCollisionMesh);
	//RootComponent = RootCollisionMesh;

	StaticMeshComponent->SetupAttachment(RootCollisionMesh);

	LiquidMesh->SetupAttachment(StaticMeshComponent);

	CapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cap Mesh"));
	CapMesh->SetupAttachment(StaticMeshComponent);


	MyCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MyCollisionSphere->InitSphereRadius(SphereRaidus);
	MyCollisionSphere->SetCollisionProfileName("Trigger");
	MyCollisionSphere->SetupAttachment(StaticMeshComponent);
}

// Called when the game starts or when spawned
void APipette::BeginPlay()
{
	Super::BeginPlay();

	Text = Cast<UTextRenderComponent>(GetDefaultSubobjectByName(FName("TextRender")));
	if (!Text)
	{
		UE_LOG(LogTemp, Error, TEXT("Text Renderer not found"));
		return;
	}

	Text->SetText(FText::FromString((TEXT("Grab G"))));

	State = Cast<UTextRenderComponent>(GetDefaultSubobjectByName(FName("Stat")));

	if (!State)
	{
		UE_LOG(LogTemp, Error, TEXT("State not found"));
		return;
	}

	MyCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APipette::OnOverlapBegin);
	MyCollisionSphere->OnComponentEndOverlap.AddDynamic(this, &APipette::OnOverlapEnd);
}

// Called every frame
void APipette::Tick(float DeltaTime)
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


void APipette::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this))
	{
		if (Cast<AFoodContainer>(OtherActor))
		{
			FoodContainer = Cast<AFoodContainer>(OtherActor);
			State->SetText(FText::FromString("Press F to Fill"));
		}
	}
}

void APipette::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                            int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this))
	{
		if (Cast<AFoodContainer>(OtherActor))
		{
			FoodContainer = nullptr;
			State->SetText(FText::FromString(""));
		}
		else if (FoodContainer)
		{
			FoodContainer = nullptr;
			State->SetText(FText::FromString(""));

		}
	}
}

void APipette::StartAction_Implementation()
{
	Super::StartAction_Implementation();
	if (!FoodContainer)
	{
		UE_LOG(LogTemp, Error, TEXT("Not WaterContainer"));
		return;
	}
	Liquid = Cast<UScaleLerp>(GetComponentByClass(UScaleLerp::StaticClass()));

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
	StaticMeshComponent->SetCollisionProfileName(FName("OverlapAll"));
	StaticMeshComponent->AttachToComponent(FoodContainer->GetRootComponent(),
	                                       FAttachmentTransformRules::KeepWorldTransform);
}

void APipette::StopAction_Implementation()
{
	Super::StopAction_Implementation();
	StaticMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	StaticMeshComponent->SetCollisionProfileName(FName("BlockAll"));
}


bool APipette::GetIsFilledWithLiquid()
{
	return IsFilledWithLiquid;
}

void APipette::SetIsFilledWithLiquid(bool Value)
{
	IsFilledWithLiquid = Value;
}
