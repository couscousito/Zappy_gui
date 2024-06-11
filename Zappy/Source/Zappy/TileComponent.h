// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Containers/Map.h"
#include "ObjectPathManager.h"
#include "TileComponent.generated.h"

USTRUCT(BlueprintType)
struct FEggInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EggId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Coordinate;
};


UCLASS()
class ZAPPY_API ATileComponent : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATileComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void PlaceObject(const FString PathToObject, FVector Location, FRotator Rotation);
	void PlaceObjectList(TMap<EObjectType, int32> ObjectList);
	void SetTileLocation(const FVector Location);
	
	// Egg Operation
	void PlaceEgg(int32 EggId, int32 PlayerId, int32 posX, int32 posY);
	void DestroyEgg(const int32 EggId);
	bool IsEggInArray(int32 EggIdToFind);
	TArray<FEggInfo> GetTileEggInfos();
	
	UStaticMeshComponent* TileMesh;
private:
	bool AreTMapIdentical(const TMap<EObjectType, int32>& Map1, const TMap<EObjectType, int32>& Map2);
	FVector TileLocation;
	UPROPERTY()
	UObjectPathManager* PathManager;
	TMap<EObjectType, int32> ObjectOnTile;
	TArray<FEggInfo> EggOnTile;
};
