
#include "TurretEnemy.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATurretEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank)
	{
		//Find the Distance to the Tank
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
	
		// Check to see if the Tank is in range
		if (Distance <= FireRange)
		{
			RotateTurret(Tank->GetActorLocation());
		}

		// If in range, Rotate to the location of the tank

	}

}

void ATurretEnemy::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}