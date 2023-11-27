// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ArenaController.generated.h"

UCLASS()
class BALANCE_API AArenaController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AArenaController();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ArenaMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// movement controls
	void MoveYaw(float Value);
	void MovePitch(float Value);

	UFUNCTION(BlueprintCallable, Category = "Reset")
	void ResetArena();


private:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;


	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationSpeed = 10.0f;
	// Variable to control the distance between the camera and the player

	// part 2 1
	UPROPERTY(EditAnywhere, Category = "Movement")
	float CameraDistance = 500.0f;
	float CameraHeight = 200.0f;
	// variable to store the ball
	// Find all actors with the "Player" tag
	AActor* Player;

};
