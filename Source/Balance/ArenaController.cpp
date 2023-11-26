// Fill out your copyright notice in the Description page of Project Settings.


#include "ArenaController.h"
//1st Mesh
#include "Components/StaticMeshComponent.h"
// 2nd camera
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
AArenaController::AArenaController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//1st
	ArenaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArenaMesh"));
	SetRootComponent(ArenaMesh);
	//part 2  1 comment this out
	//ArenaMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f)); 

	// 2nd camera
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 500.0f)); 
	SpringArmComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f)); 

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	CameraComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));//part 2 1 changed from -20 t 0 on x
}

// Called when the game starts or when spawned
void AArenaController::BeginPlay()
{
	Super::BeginPlay();
	ArenaMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	SpringArmComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	CameraComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));//part 2 1 changed from -20 t 0 on x
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
	SetActorRotation(NewRotation);
}
