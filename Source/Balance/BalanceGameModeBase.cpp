// Copyright Epic Games, Inc. All Rights Reserved.


#include "BalanceGameModeBase.h"
#include "ArenaController.h"
#include "Kismet/GameplayStatics.h"

void ABalanceGameModeBase::StartPlay()
{
	Super::StartPlay();

	// The arena
	AArenaController* arena = GetWorld()->SpawnActor<AArenaController>(AArenaController::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);


	if (arena)
	{
		// Pass the controller
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController)
		{
			PlayerController->Possess(arena);
		}
	}
}