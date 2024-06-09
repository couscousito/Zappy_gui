// Copyright Epic Games, Inc. All Rights Reserved.


#include "ZappyGameModeBase.h"

void AZappyGameModeBase::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("enter in entry point"));
	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation = FRotator::ZeroRotator;

	if (GetWorld())
	{
		FString ProtocolString = "BCT 0 0 1 1 0 0 0 1 1\nBCT 0 1 1 0 1 1 0 0 0\nBCT 0 2 0 1 1 0 1 0 0\nBCT 1 0 0 1 0 0 0 1 0\nBCT 1 1 1 1 0 1 0 0 0\nBCT 1 2 0 0 1 0 0 0 0\nBCT 2 0 1 1 0 1 0 0 0\nBCT 2 1 0 0 1 0 1 0 0\nBCT 2 2 1 1 0 0 0 0 0\n";
		GameMap = GetWorld()->SpawnActor<AGameMap>(Location, Rotation);
		if (GameMap)
		{
			GameMap->InitMap(3, 3);
			GameMap->GenerateMap();
			GameMap->SetObjectOnMapByProtocol(ProtocolString);
		}
	}
}
