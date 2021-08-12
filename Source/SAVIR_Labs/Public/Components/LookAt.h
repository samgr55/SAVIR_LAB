// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "LookAt.generated.h"

class UCharacterMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAVIR_LABS_API ULookAt : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULookAt();

	void StartLookAt(TArray<AActor*>* InLookAtActors, TArray<float>* InLookAtTimeInSecond);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	TArray<AActor*>* LookAtActors;
	TArray<float>* LookAtTimeInSecond;

	int32 Index = 0;

	void LookAtActor();

	FTimerHandle LookAtActorTimerHandle;

	UPROPERTY()
	UCharacterMovementComponent* MovementComponent;

	UPROPERTY()
	USpringArmComponent* CameraBoom;

		
};




