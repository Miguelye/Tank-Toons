// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TurretEnemy.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurretEnemy : public ABasePawn
{
	GENERATED_BODY()
	
public:

	virtual void Tick(float DeltaTime);

	void HandleDestruction();

protected:

	//Called whe the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		float FireRange = 500.f;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		float FireRate = 2.f;

	FTimerHandle FireRateTimerHandle;
	void CheckFireCondition();
	bool InFireRange();


	class ATank* Tank;
};
