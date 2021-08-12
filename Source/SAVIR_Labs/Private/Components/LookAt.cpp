// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LookAt.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
ULookAt::ULookAt()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



// Called when the game starts
void ULookAt::BeginPlay()
{
	Super::BeginPlay();
	if(!GetOwner())
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Get Owner in ULookAt::BeginPlay"));
		return;
	}
	MovementComponent = Cast<UCharacterMovementComponent>(GetOwner()->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	if(!MovementComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Get MovementComponent in ULookAt::BeginPlay"));
		return;
	}

	CameraBoom = Cast<USpringArmComponent>(GetOwner()->GetComponentByClass(USpringArmComponent::StaticClass()));

	if(!CameraBoom)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Get CameraBoom in ULookAt::BeginPlay"));
		return;
	}
}


// Called every frame
void ULookAt::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void ULookAt::StartLookAt(TArray<AActor*>* InLookAtActors, TArray<float>* InLookAtTimeInSecond)
{
	LookAtActors = InLookAtActors;
	LookAtTimeInSecond = InLookAtTimeInSecond;
	
	if(!MovementComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("MovementComponent is nullptr! in ULookAt::StartLookAt"));
		return;
	}
	MovementComponent->SetActive(false);
	//MovementComponent->MaxWalkSpeed = 0.f;

	Index = 0;
	LookAtActor();
}

void ULookAt::LookAtActor()
{
	if(!CameraBoom || !MovementComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant GetCameraBoom Or MovementComponent in ULookAt::LookAtActor"));
		return;
	}
	if(Index >= LookAtActors->Num())
	{
		MovementComponent->SetActive(true);
		return;
	}
	
	CameraBoom->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(),
		LookAtActors->GetData()[Index]->GetActorLocation()));
	
	GetOwner()->GetWorldTimerManager().SetTimer(LookAtActorTimerHandle, this,
		&ULookAt::LookAtActor, LookAtTimeInSecond->GetData()[Index]);
	Index++;
	
}