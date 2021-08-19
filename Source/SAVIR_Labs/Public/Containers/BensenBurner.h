// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/LabToolContainer.h"
#include "BensenBurner.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SAVIR_LABS_API ABensenBurner : public ALabToolContainer
{
	GENERATED_BODY()

public:
	ABensenBurner();

	UFUNCTION(BlueprintCallable)
	void StartBensenAction();
	
	UFUNCTION(BlueprintCallable)
	void StopBensenAction();

	void BensenAction();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	FString ActionMessage;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess), Category=Bensen)
	bool bIsHot;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess), Category=Bensen)
	bool bIsGrabbedByTong;
	

private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess), Category=Bensen)
	bool bIsActionActive;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess), Category=Bensen)
	UParticleSystemComponent* FirePS;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess), Category=Bensen)
	UParticleSystemComponent* GasPS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess), Category=Bensen)
	float BoilingTimeInSecond;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess), Category=Bensen)
	float CoolingTimeInSecond;


	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess), Category=Bensen)
	bool bIsAPlayerInRange;

private:
	
	UFUNCTION()
	void StartBoiling();

	UFUNCTION()
	void StopBoiling();
	
	FTimerHandle TimerHandle;
	
};
