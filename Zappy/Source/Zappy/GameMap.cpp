// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMap.h"

#include "GameCharacter.h"
#include "Trace/Detail/Protocols/Protocol0.h"

// Sets default values
AGameMap::AGameMap(const int32 SizeXParam, const int32 SizeYParam): SizeX(10), SizeY(10)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

template<typename T>
bool AreArraysEqual(const TArray<T>& Array1, const TArray<T>& Array2)
{
	// Check if the sizes are the same
	if (Array1.Num() != Array2.Num())
	{
		return false;
	}

	// Compare each element
	for (int32 i = 0; i < Array1.Num(); i++)
	{
		if (Array1[i] != Array2[i])
		{
			return false;
		}
	}

	return true;
}

void AGameMap::GenerateMap()
{
	UE_LOG(LogTemp, Warning, TEXT("Enter in map generator with size %d | %d"), SizeX, SizeY);

	for (int32 x = 0; x < SizeX; x++)
	{
		for (int32 y = 0; y < SizeY; y++)
		{
			FVector Location(x * 420.0f, y * 420.0f, 0.0f);
			FRotator Rotation = FRotator::ZeroRotator	;
			// FActorSpawnParameters SpawnParams;
			ATileComponent *Tile = GetWorld()->SpawnActor<ATileComponent>(ATileComponent::StaticClass(), Location, Rotation);
			FTileInfo TileInfo;
			TileInfo.TileID = FCString::Atoi(*FString::Printf(TEXT("%d%d"), x, y));
			TileInfo.TileComponent = Tile;
			Tile->SetTileLocation(Location);
			TileMap.Add(TileInfo);
		}
	}
}

FTileInfo *AGameMap::GetTileById(const int32 TileId)
{
	FTileInfo* FoundTile = TileMap.FindByPredicate([TileId](const FTileInfo& Tile)
	{
		return Tile.TileID == TileId;
	});
	return FoundTile;
}


void AGameMap::SetObjectOnMapByProtocol(TArray<FString> &ProtocolArray)
{
	if (ProtocolArray.Num() != 10)
	{
		UE_LOG(LogTemp, Warning, TEXT("Error: Bad protocol string"));
		return;
	}
	const int32 TileId = FCString::Atoi(*(ProtocolArray[1] + ProtocolArray[2]));
	const FTileInfo *CorrespondingTile = GetTileById(TileId);
	ProtocolArray.RemoveAt(0, 3);
	
	if (!AreArraysEqual(ProtocolArray, CorrespondingTile->TileComponent->OldProtocol))
	{
		CorrespondingTile->TileComponent->OldProtocol = ProtocolArray;
		for (int32 CrystalIndex = 0; CrystalIndex < ProtocolArray.Num(); CrystalIndex++)
		{
			for (int32 Index = 0; Index < FCString::Atoi(*ProtocolArray[CrystalIndex]); Index++)
			{
				CorrespondingTile->TileComponent->PlaceObjectByType(CrystalIndex);
			}
		}
	}
}

void AGameMap::SetEggOnMap(const TArray<FString> &ProtocolArray)
{
	int32 TileId = FCString::Atoi(*(ProtocolArray[3] + ProtocolArray[4]));
	for (FTileInfo TileInfo: TileMap)
	{
		if (TileInfo.TileID == TileId)
		{
			TileInfo.TileComponent->PlaceEgg(FCString::Atoi(*ProtocolArray[1]), FCString::Atoi(*ProtocolArray[1]), FCString::Atoi(*ProtocolArray[3]), FCString::Atoi(*ProtocolArray[4]));
		}
	}
}

void AGameMap::DestroyEggById(const int32 EggId)
{
	for (FTileInfo TileInfo: TileMap)
	{
		if (TileInfo.TileComponent->IsEggInArray(EggId))
		{
			TileInfo.TileComponent->DestroyEgg(EggId);
		}
	}
}

void AGameMap::SpawnCharacter(const TArray<FString>& ProtocolArray)
{
	int32 TileId = FCString::Atoi(*(ProtocolArray[2] + ProtocolArray[3]));
	FVector Location;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	
	for (FTileInfo TileInfo: TileMap)
	{
		if (TileInfo.TileID == TileId && TileInfo.TileComponent->IsEggInArray())
		{
			DestroyEggById(TileInfo.TileComponent->GetTileEggInfos()[0].EggId);
			Location = TileInfo.TileComponent->GetTileLocation() + 100.0f;
		}
	}
	AGameCharacter *NewCharacter = GetWorld()->SpawnActor<AGameCharacter>(AGameCharacter::StaticClass(), Location, FRotator::ZeroRotator, SpawnParams);
	FCharacterInfo NewCharacterInfo;
	NewCharacterInfo.Character = NewCharacter;
	NewCharacterInfo.CharacterId = ProtocolArray[1];
	CharacterArray.Add(NewCharacterInfo);
}

void AGameMap::InitMap(const int32 SizeXParam, const int32 SizeYParam)
{
	SizeX = SizeXParam;
	SizeY = SizeYParam;
}

// Called when the game starts or when spawned
void AGameMap::BeginPlay()
{
	Super::BeginPlay();
	GenerateMap();
}

// Called every frame
void AGameMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
