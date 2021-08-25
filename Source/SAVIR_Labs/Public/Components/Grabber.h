// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "Containers/LiquidContiner.h"
#include "Containers/Pipette.h"
#include "Containers/Thermometer.h"
#include "PhysicsEngine/PhysicsHandleComponent.h" 
#include "Grabber.generated.h"

class UInputComponent;
class AInformationActor;
class USkeletalMeshSocket;
class AChemicalContainer;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SAVIR_LABS_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnyWhere, Category = "Hands")
		USkeletalMeshSocket* RightHandSocket;
	UPROPERTY(EditAnyWhere, Category = "Hands")
		USkeletalMeshSocket* LeftHandSocket;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	bool bIsGrabbing = false;
	bool bIsShowingData = false;
	bool bIsAction;

	UPROPERTY()
	ACharacter* OwnerCharacter;
	
	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UPROPERTY()
	UInputComponent* InputComponent = nullptr;

	UPROPERTY()
	AInformationActor* GrabbedContainer;

	UPROPERTY()
	AThermometer* ThermometerContainer;
	
	UPROPERTY()
	APipette* PipetteContainer;
	
	UPROPERTY()
	USceneComponent* GrabbedRoot;

	UPROPERTY()
	AInformationActor* InformationActor;
 
	UPROPERTY(EditAnywhere)
	float Reach = 100.0f;

	void Grab();
	void Release();
	void SetupInputComponent();
	void ShowData();

	UFUNCTION()
	void Action();

	UFUNCTION()
	void StartAction();

	UFUNCTION()
	void StopAction();

	//Return The first actor within reach with physics body
	FHitResult GetFirstPhysicsBodyInReach() const;

	//Return The Line Trace End
	FVector GetPlayerReach() const;

	//Get Player Position in world
	FVector GetPlayerWorldPos() const;
};
