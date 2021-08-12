// Fill out your copyright notice in the Description page of Project Settings.


#include "LabTools/LabToolContainer.h"

#include "Widgets/ToolInfoWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values
ALabToolContainer::ALabToolContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = StaticMeshComp;
}

// Called when the game starts or when spawned
void ALabToolContainer::BeginPlay()
{
	Super::BeginPlay();

	OriginalPosition = GetActorLocation();
	OriginalRotation = GetActorRotation().Quaternion();

	OnActorHit.AddDynamic(this, &ALabToolContainer::OnHit);

	WidgetComponent = Cast<UWidgetComponent>(GetComponentByClass(UWidgetComponent::StaticClass()));
	
	if(WidgetComponent)
	{
		auto Widget = Cast<UToolInfoWidget> (WidgetComponent->GetWidget());
		if(Widget)
		{
			ToolElement = DataTable->FindRow<FLabTools>(FName(FString::FromInt(ToolID)), "");
			Description = ToolElement->Description;
	
			ImageDescription = NewObject<UImage>(GetWorld());
			ImageDescription->SetBrushFromTexture(ToolElement->Image);

			Widget->SetUpWidget(ToolElement);
			Widget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	
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