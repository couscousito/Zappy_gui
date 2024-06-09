// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMap.h"

#include "Trace/Detail/Protocols/Protocol0.h"

// Sets default values
AGameMap::AGameMap(const int32 SizeXParam, const int32 SizeYParam): SizeX(10), SizeY(10)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
			TileInfo.TileID = FString::Printf(TEXT("%d%d"), x, y);
			TileInfo.TileComponent = Tile;
			Tile->SetTileLocation(Location);
			TileMap.Add(TileInfo);
		}
	}
}

TArray<FString> AGameMap::SplitProtocolString(const FString& InputString, const FString& Delimiter, const FString &ProtocolID)
{
	TArray<FString> ProtocolArray;
	FString remainingString = InputString;
	int32 pos;

	while ((pos = remainingString.Find(Delimiter)) != -1)
	{
		FString Substring = remainingString.Left(pos).Replace(*ProtocolID, TEXT(""), ESearchCase::IgnoreCase);
		ProtocolArray.Add(Substring);
		remainingString = remainingString.Mid(pos + Delimiter.Len());
	}
	return ProtocolArray;
}

void AGameMap::SetObjectOnMapByProtocol(FString &ProtocolString)
{
	TArray<FString> ProtocolArray = SplitProtocolString(ProtocolString, TEXT("\n"), TEXT("BCT "));
	FString TileId;
	
	for (FString Protocol: ProtocolArray)
	{
		UE_LOG(LogTemp, Warning, TEXT("protocol String : %s"), *Protocol);
		TArray<FString> ProtocolArgs;
		TMap<EObjectType, int32> ObjectsNumber;
		Protocol.ParseIntoArray(ProtocolArgs, TEXT(" "), true);
		if (ProtocolArgs.Num() != 9)
		{
			UE_LOG(LogTemp, Warning, TEXT("Error: Bad protocol string %s"), *Protocol);
			return;
		}
		
		TileId = ProtocolArgs[0] + ProtocolArgs[1];
		ObjectsNumber.Add(EObjectType::Food, FCString::Atoi(*ProtocolArgs[2]));
		ObjectsNumber.Add(EObjectType::Linemate, FCString::Atoi(*ProtocolArgs[3]));
		ObjectsNumber.Add(EObjectType::Deraumere, FCString::Atoi(*ProtocolArgs[4]));
		ObjectsNumber.Add(EObjectType::Sibur, FCString::Atoi(*ProtocolArgs[5]));
		ObjectsNumber.Add(EObjectType::Mendiane, FCString::Atoi(*ProtocolArgs[6]));
		ObjectsNumber.Add(EObjectType::Phiras, FCString::Atoi(*ProtocolArgs[7]));
		ObjectsNumber.Add(EObjectType::Thystame, FCString::Atoi(*ProtocolArgs[8]));
		UE_LOG(LogTemp, Warning, TEXT("Tile ID : %s"), *TileId);
		for (FTileInfo TileInfo: TileMap)
		{
			if (TileInfo.TileID == TileId)
			{
				TileInfo.TileComponent->PlaceObjectList(ObjectsNumber);
			}
		}
	}
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

