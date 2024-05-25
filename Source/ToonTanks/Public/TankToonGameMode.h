// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankToonGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankToonGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	void ActorDied(AActor* DeadActor);

protected:

	virtual void BeginPlay() override;

	//BlueprintImplementableEvent means that the implementation can be define in blueprints
	//the function can still be called in code.
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

private:


	class ATank* Tank;
	class AToonTankPlayerController* ToonTankPlayerController;

	//Timer Before Game Starts
	float StartDelay = 3.f;

	void HandleGameStart();

};
