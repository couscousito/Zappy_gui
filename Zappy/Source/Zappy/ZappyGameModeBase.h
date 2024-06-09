// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameMap.h"
#include "ProtocolManager.h"
#include "GameFramework/GameModeBase.h"
#include "ZappyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ZAPPY_API AZappyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
private:
	UPROPERTY();
	AProtocolManager* ProtocolManager;
};
