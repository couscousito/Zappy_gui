// Copyright Epic Games, Inc. All Rights Reserved.


#include "ZappyGameModeBase.h"

void AZappyGameModeBase::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("enter in entry point"));
	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation = FRotator::ZeroRotator;

	if (GetWorld())
	{
		ProtocolManager = GetWorld()->SpawnActor<AProtocolManager>(AProtocolManager::StaticClass());
	}
}
