// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"


ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArm);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent); //Call the parent version

	// Get the player controller
	auto playerController = Cast<APlayerController>(GetController());

	// Get the local player enhanced input subsystem
	auto eiSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

	//Add the input mapping context
	eiSubsystem->AddMappingContext(inputMapping, 0);

	// Get the EnhancedInputComponent
	auto playerEIcomponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Bind Move() to the mapping
	//BindAction for enhanced system takes Action, ETriggerEvent, object, and function
	//ETriggerEvent is an enum, where Triggered means "button is held down".
	playerEIcomponent->BindAction(inputMove, ETriggerEvent::Triggered, this, &ATank::Move);
	playerEIcomponent->BindAction(inputTurn, ETriggerEvent::Triggered, this, &ATank::Turn);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerControllerRef)
	{
		FHitResult HitResult;

		PlayerControllerRef->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility, 
			false, 
			HitResult);
		
		//DrawDebugSphere(
		//	GetWorld(),
		//	HitResult.ImpactPoint,
		//	20.f,
		//	12,
		//	FColor::Red,
		//	false,
		//	-1.f);

		RotateTurret(HitResult.ImpactPoint);
	}


}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATank::Move(const FInputActionValue& Value) 
{
	//UE_LOG(LogTemp, Display, TEXT("Float Move value: %f"), Value.Get<float>());

	FVector DeltaLocation = FVector::ZeroVector;

	//DeltaTime
	auto dt = UGameplayStatics::GetWorldDeltaSeconds(this);

	// X = Value * DeltaTime * Speed
	DeltaLocation.X = Value.Get<float>() * speed * dt;

	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("Float Turn value: %f"), Value.Get<float>());

	FRotator DeltaRotation = FRotator::ZeroRotator;

	//DeltaTime
	auto dt = UGameplayStatics::GetWorldDeltaSeconds(this);

	//Yaw * DeltaTime * TurnRate
	DeltaRotation.Yaw = Value.Get<float>() * dt * turnRate;
	AddActorLocalRotation(DeltaRotation, true);
}