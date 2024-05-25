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

		GameOver(false);
	}
	else if (ATurretEnemy* DestroyedTurret = Cast<ATurretEnemy>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
		TargetTurrets--;
		if (TargetTurrets <= 0)
		{
			GameOver(true);
		}
	}
}


void ATankToonGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();


}

void ATankToonGameMode::HandleGameStart()
{
	TargetTurrets = GetTargetTurretCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTankPlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

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

int32 ATankToonGameMode::GetTargetTurretCount()
{
	TArray<AActor*> Turrets;

	//This will fill the arrays with how many turret are in the game.
	UGameplayStatics::GetAllActorsOfClass(this, ATurretEnemy::StaticClass(), Turrets);

	//this return the total amount of turret.
	return Turrets.Num();
}