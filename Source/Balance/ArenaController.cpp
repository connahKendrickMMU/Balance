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
	// Set the static mesh asset
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Arena>Arena"));
	if (MeshAsset.Succeeded())
	{
		ArenaMesh->SetStaticMesh(MeshAsset.Object);
	}

	// 2nd camera
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void AArenaController::BeginPlay()
{
	Super::BeginPlay();
	
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
