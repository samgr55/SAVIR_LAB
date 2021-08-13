// Fill out your copyright notice in the Description page of Project Settings.


#include "General/InstructionTriggerBox.h"

#include "Components/LookAt.h"
#include "Widgets/InstructionsHUD.h"
#include "Widgets/InstructionsWidget.h"

AInstructionTriggerBox::AInstructionTriggerBox()
{
	OnActorBeginOverlap.AddDynamic(this, &AInstructionTriggerBox::OnOverlap);
}

void AInstructionTriggerBox::OnOverlap(AActor* ThisActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Error, TEXT("OnOverlap !"))

	if(!GetWorld() || !GetWorld()->GetFirstPlayerController())
	{
		UE_LOG(LogTemp, Error, TEXT("Fetal Unresonable Error in AInstructionTriggerBox::OnOverlap !"))
		return;
	}
	auto HUD = GetWorld()->GetFirstPlayerController()->GetHUD<AInstructionsHUD>();
	
	if(!HUD)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Get or Cast HUD in AInstructionTriggerBox::OnOverlap !"))
		return;
	}
	
	auto InstructionsWidget = HUD->GetInstructionsWidget();
	if(!InstructionsWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Get InstructionsWidget in AInstructionTriggerBox::OnOverlap !"))
		return;
	}
	InstructionsWidget->StartNarrative(Title, &Narrative, &NarrativeTimeInMSecond);

	

	auto LookAtComponent = Cast<ULookAt>(OtherActor->GetComponentByClass(ULookAt::StaticClass()));
	if(!LookAtComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Get LookAtComponent in AInstructionTriggerBox::OnOverlap !"))
		return;
	}
	LookAtComponent->StartLookAt(&LookAtActors, &LookAtTimeInSecond);
}

