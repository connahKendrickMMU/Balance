// Copyright Epic Games, Inc. All Rights Reserved.


#include "BalanceGameModeBase.h"
#include "ArenaController.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

void ABalanceGameModeBase::StartPlay()
{
	Super::StartPlay();

	// The arena
	AArenaController* arena = nullptr; 
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Player"), FoundActors);

	// Check if at least one actor with the tag is found
	if (FoundActors.Num() > 0)
	{
		for (AActor* FoundActor : FoundActors)
		{
			if (FoundActor->IsA<AArenaController>())
			{
				arena = Cast<AArenaController>(FoundActor);
				break; // Found the correct type, break out of the loop
			}
		}
	}

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