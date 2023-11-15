// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BalanceGameModeBase.generated.h"


UCLASS()
class BALANCE_API ABalanceGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	//6th
	virtual void StartPlay() override;
};
