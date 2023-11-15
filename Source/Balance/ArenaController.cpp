// Fill out your copyright notice in the Description page of Project Settings.


#include "ArenaController.h"
//1st Mesh
#include "Components/StaticMeshComponent.h"
// 2nd camera
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// test code
#include "HAL/FileManagerGeneric.h"
#include "Misc/Paths.h"
// Sets default values
AArenaController::AArenaController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//1st
	ArenaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArenaMesh"));
	SetRootComponent(ArenaMesh);
	ArenaMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f)); // Adjust the values as needed

	// 2nd camera
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 500.0f)); 
	SpringArmComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f)); 

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 5.0f));
	CameraComponent->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void AArenaController::BeginPlay()
{
	Super::BeginPlay();
	
	// shift the platform up
	FVector NewLocation = GetActorLocation();
	NewLocation.Z += 100.0f; // Adjust the value based on how much you want to move it
	SetActorLocation(NewLocation);
}

// Called every frame
void AArenaController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AArenaController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 5th
	PlayerInputComponent->BindAxis("MoveYaw", this, &AArenaController::MoveYaw);
}

// 4th 
void AArenaController::MoveYaw(float Value)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += Value * RotationSpeed * GetWorld()->GetDeltaSeconds();
	SetActorRotation(NewRotation);
}
