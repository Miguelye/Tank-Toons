// Fill out your copyright notice in the Description page of Project Settings.


#include "TankToonGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TurretEnemy.h"
#include "ToonTankPlayerController.h"

void ATankToonGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTankPlayerController)
		{
			ToonTankPlayerController->SetPlayerEnabledState(false);
		}
	}
	else if (ATurretEnemy* DestroyedTurret = Cast<ATurretEnemy>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
	}
}


void ATankToonGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();


}

void ATankToonGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTankPlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (ToonTankPlayerController)
	{
		ToonTankPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;

		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTankPlayerController, 
			&AToonTankPlayerController::SetPlayerEnabledState, 
			true);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			StartDelay,
			false);

	}
}