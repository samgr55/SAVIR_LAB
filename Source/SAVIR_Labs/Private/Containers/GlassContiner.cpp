// Fill out your copyright notice in the Description page of Project Settings.


#include "Containers/GlassContiner.h"

#include "DrawDebugHelpers.h"
#include "Components/ScaleLerp.h"
#include "Components/SphereComponent.h"
//#include "Containers/LiquidContiner.h"

// Sets default values
AGlassContiner::AGlassContiner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	MyCollisionSphere->InitSphereRadius(SphereRaidus);
	MyCollisionSphere->SetCollisionProfileName("Trigger");

	RootComponent = MyCollisionSphere;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh"));
	MyMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGlassContiner::BeginPlay()
{
	Super::BeginPlay();

	MyCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AGlassContiner::OnOverlapBegin);
}

// Called every frame
void AGlassContiner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRaidus, 20, FColor::Purple, false, -1, 0, 1);
}

void AGlassContiner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		// if ((OtherActor = Cast<AthermometerContainer>(OtherActor)) != nullptr)
		// {
		// 	auto Liquid = Cast<UScaleLerp>(OtherActor->GetComponentByClass(UScaleLerp::StaticClass()));
		//
		// 	if (!Liquid)
		// 	{
		// 		UE_LOG(LogTemp, Error, TEXT(" Not found Scale Lerp"));
		// 		return;
		// 	}
		//
		// 	auto scale = Cast<UScaleLerp>(this->GetComponentByClass(UScaleLerp::StaticClass()));
		// 	if(!scale)
		// 	{
		// 		UE_LOG(LogTemp, Error, TEXT(" Not found Scale"));
		// 		return;
		// 	}
		// 	
		// 	scale->InitiateScale();
		//
		// 	UE_LOG(LogTemp, Error, TEXT("Overlap Begin With"));
		// }
	}
}
