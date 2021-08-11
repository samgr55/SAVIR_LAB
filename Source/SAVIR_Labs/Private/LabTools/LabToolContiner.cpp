// Fill out your copyright notice in the Description page of Project Settings.


#include "LabTools/LabToolContiner.h"

#include "ToolInfoWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values
ALabToolContiner::ALabToolContiner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = StaticMeshComp;
}

// Called when the game starts or when spawned
void ALabToolContiner::BeginPlay()
{
	Super::BeginPlay();

	OriginalPosition = GetActorLocation();
	OriginalRotation = GetActorRotation().Quaternion();

	OnActorHit.AddDynamic(this, &ALabToolContiner::OnHit);

	WidgetComponent = Cast<UWidgetComponent>(GetComponentByClass(UWidgetComponent::StaticClass()));
	
	if(WidgetComponent)
	{
		auto Widget = Cast<UToolInfoWidget> (WidgetComponent->GetWidget());
		if(Widget)
		{
			ToolElement = ElementsArray->GetToolById(ToolID);
			Description = ToolElement->Description;
	
			ImageDescription = NewObject<UImage>(GetWorld());
			ImageDescription->SetBrushFromTexture(ToolElement->Image);

			Widget->SetUpWidget(ToolElement);
		}
	}

	WidgetComponent->GetWidget()->SetVisibility(ESlateVisibility::Collapsed);
}

// Called every frame
void ALabToolContiner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALabToolContiner::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OriginalParent)
	{
		UE_LOG(LogTemp, Warning, TEXT("HIT other"));
		OriginalParent = OtherActor;
	}
	//if the other actor isn't self or owner and exists then applay damage.
	if (!CurrentParent && OtherActor != OriginalParent)
	{
		UE_LOG(LogTemp, Warning, TEXT("other"));
		//SetActorLocation(OriginalPosition,false,nullptr,ETeleportType::TeleportPhysics);
		SetActorLocationAndRotation(OriginalPosition, OriginalRotation, false, nullptr, ETeleportType::TeleportPhysics);
	}
}