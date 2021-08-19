// Fill out your copyright notice in the Description page of Project Settings.


#include "Containers/BensenBurner.h"

#include "Particles/ParticleSystemComponent.h"
#include "Widgets/InstructionsHUD.h"

ABensenBurner::ABensenBurner()
{
	bIsActionActive = false;
	bIsAPlayerInRange = false;
	bCanBeGrabbed = false;
	bIsHot = false;
	bIsGrabbedByTong = false;
	AutoReceiveInput = EAutoReceiveInput::Player0;
	
}

void ABensenBurner::StartBensenAction()
{
	FirePS->Activate();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABensenBurner::StartBoiling, BoilingTimeInSecond);
}

void ABensenBurner::StopBensenAction()
{
	FirePS->Deactivate();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABensenBurner::StopBoiling, CoolingTimeInSecond);
}

void ABensenBurner::BensenAction()
{
	if(!bIsAPlayerInRange)
	{
		UE_LOG(LogTemp, Error, TEXT("No Player In Range for %s"), *GetName());
		return;
	}
	if(bIsActionActive)
	{
		bIsActionActive = false;
		StopBensenAction();
	}
	else
	{
		bIsActionActive = true;
		StartBensenAction();
	}
}

void ABensenBurner::BeginPlay()
{
	Super::BeginPlay();
	if(!InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Get ThisInputComponent! in BensenBurner::BeginPlay"));
		return;
	}
	auto Input = InputComponent->BindAction("Ignite", IE_Pressed, this, &ABensenBurner::BensenAction);
	Input.bConsumeInput = false;
	FirePS = Cast<UParticleSystemComponent>(GetDefaultSubobjectByName(TEXT("Fire_PS")));
	if(!FirePS)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Get Fire_PS! in BensenBurner::BeginPlay"));
		return;
	}
	GasPS = Cast<UParticleSystemComponent>(GetDefaultSubobjectByName(TEXT("Gas_PS")));
	if(!GasPS)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Get Gas_PS! in BensenBurner::BeginPlay"));
		return;
	}
}

void ABensenBurner::StartBoiling()
{
	GasPS->Activate();
	bIsHot = true;
	auto HUD = GetWorld()->GetFirstPlayerController()->GetHUD<AInstructionsHUD>();
	if(!HUD)
	{
		return;
	}
	HUD->ShowActionWidget(ActionMessage);
}

void ABensenBurner::StopBoiling()
{
	GasPS->Deactivate();
	bIsHot = false;
	auto HUD = GetWorld()->GetFirstPlayerController()->GetHUD<AInstructionsHUD>();
	if(!HUD)
	{
		return;
	}
	HUD->HideActionWidget();
}
