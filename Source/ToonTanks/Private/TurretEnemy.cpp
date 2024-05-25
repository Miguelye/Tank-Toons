
#include "TurretEnemy.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATurretEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check to see if the Tank is in range
	if (InFireRange())
	{
		// If in range, Rotate to the location of the tank
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATurretEnemy::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurretEnemy::CheckFireCondition, FireRate, true);
}

void ATurretEnemy::HandleDestruction()
{
	//Called the function from based class
	Super::HandleDestruction();
	Destroy();
}

void ATurretEnemy::CheckFireCondition()
{
	// Check to see if the Tank is in range
	if (InFireRange())
	{
		// If in range, fire to the location of the tank
		Fire();
	}
}

bool ATurretEnemy::InFireRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if (Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}