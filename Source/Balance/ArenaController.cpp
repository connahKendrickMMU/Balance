// Fill out your copyright notice in the Description page of Project Settings.


#include "ArenaController.h"
//1st Mesh
#include "Components/StaticMeshComponent.h"
// 2nd camera
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
// need for get all actors
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AArenaController::AArenaController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//1st
	ArenaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArenaMesh"));
	SetRootComponent(ArenaMesh);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
}

// Called when the game starts or when spawned
void AArenaController::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundPlayers;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Ball"), FoundPlayers);
	// check how many players where found
	UE_LOG(LogTemp, Warning, TEXT("players found: %d"), FoundPlayers.Num());
	// Check if we have a player
	if (FoundPlayers.Num() > 0)
	{
		Player = FoundPlayers[0];
	}
}

// Called every frame
void AArenaController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// part 2 2
	if (Player != nullptr)
	{
		// distance the camera from the player
		FVector NewCameraLocation = Player->GetActorLocation() - (FVector::ForwardVector * CameraDistance) + FVector(0,0,CameraHeight);

		// place the camera
		CameraComponent->SetWorldLocation(NewCameraLocation);

		// lookat the player, this can be adjusted to a one time setting but can effect rotation
		FVector LookAtPlayer = Player->GetActorLocation();

		CameraComponent->SetWorldRotation((LookAtPlayer - CameraComponent->GetComponentLocation()).Rotation());
		FRotator NewCameraRotation = UKismetMathLibrary::FindLookAtRotation(CameraComponent->GetComponentLocation(), LookAtPlayer);
		UE_LOG(LogTemp, Warning, TEXT("Grabber Rotation: %s"), *NewCameraRotation.ToString());
		CameraComponent->SetRelativeRotation(NewCameraRotation);
	}
}

// Called to bind functionality to input
void AArenaController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveYaw", this, &AArenaController::MoveYaw);
	PlayerInputComponent->BindAxis("MovePitch", this, &AArenaController::MovePitch);
}

// 4th 
void AArenaController::MoveYaw(float Value)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += Value * RotationSpeed * GetWorld()->GetDeltaSeconds();
	SetActorRotation(NewRotation);
}

void AArenaController::MovePitch(float Value)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Pitch += Value * RotationSpeed * GetWorld()->GetDeltaSeconds();
	//NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch, MinPitch, MaxPitch);
	SetActorRotation(NewRotation);
}

void AArenaController::ResetArena()
{

	SetActorRotation(FRotator::ZeroRotator);
}