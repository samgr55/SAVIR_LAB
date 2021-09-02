// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/WaterContainer.h"
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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnyWhere, Category = "Hands")
	USkeletalMeshSocket* RightHandSocket;
	UPROPERTY(EditAnyWhere, Category = "Hands")
	USkeletalMeshSocket* LeftHandSocket;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	AInformationActor* HideInfo;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool bIsHandGrabbing;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool bIsLineGrabbing;

	UPROPERTY()
	ACharacter* OwnerCharacter;


	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	AInformationActor* HandGrabbedActor;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	AInformationActor* LineGrabbedActor;


	UPROPERTY()
	USceneComponent* HandGrabbedRoot;

	UPROPERTY()
	AInformationActor* ActionGrabbed;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float Reach = 100.0f;

	UFUNCTION(BlueprintCallable)
	void Grab();
	UFUNCTION(BlueprintCallable)
	void Release();
	UFUNCTION(BlueprintCallable)
	void SetupInputComponent();
	UFUNCTION(BlueprintCallable)
	void ShowData();
	UFUNCTION(BlueprintCallable)
	void HideData();
	UFUNCTION(BlueprintCallable)
	void GrabWithHand();
	UFUNCTION(BlueprintCallable)
	void GrabWithLine();

	UFUNCTION(BlueprintCallable)
	void Action();

	UFUNCTION(BlueprintCallable)
	void StartHandAction();

	UFUNCTION(BlueprintCallable)
	void StartLineAction();

	UFUNCTION()
	void StopHandAction();

	UFUNCTION()
	void StopLineAction();

	//Return The first actor within reach with physics body
	FHitResult GetFirstPhysicsBodyInReach() const;

	//Return The Line Trace End
	FVector GetPlayerReach() const;

	//Get Player Position in world
	FVector GetPlayerWorldPos() const;
};
