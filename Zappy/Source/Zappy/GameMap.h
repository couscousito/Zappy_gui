// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileComponent.h"
#include "Containers/Array.h"
#include "GameCharacter.h"
#include "GameMap.generated.h"

USTRUCT(BlueprintType)
struct FTileInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TileID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATileComponent* TileComponent;
};

USTRUCT(BlueprintType)
struct FCharacterInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CharacterId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AGameCharacter* Character;
};

UCLASS()
class ZAPPY_API AGameMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameMap(const int32 SizeXParam, const int32 SizeYParam);
	AGameMap() : SizeX(0), SizeY(0){};
	void InitMap(const int32 SizeXParam, const int32 SizeYParam);
	void GenerateMap();
	void SetObjectOnMapByProtocol(TArray<FString> &ProtocolArray);
	void SetEggOnMap(const TArray<FString> &ProtocolArray);
	void DestroyEggById(const int32 EggId);
	void SpawnCharacter(const TArray<FString> &ProtocolArray);
	FTileInfo *GetTileById(const int32 TileId);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	// TArray<FString> SplitProtocolString(const FString& InputString, const FString& Delimiter, const FString &ProtocolID);
	TArray<FTileInfo> TileMap;
	TArray<FCharacterInfo> CharacterArray;
	int32 SizeX;
	int32 SizeY;
};
