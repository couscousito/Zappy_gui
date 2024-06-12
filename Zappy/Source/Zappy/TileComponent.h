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
	UStaticMeshComponent *EggMesh;
};

USTRUCT(BlueprintType)
struct FObjectInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EObjectType ObjectType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ObjectId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent *ObjectMesh;
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
	UStaticMeshComponent* PlaceObject(const FString& PathToObject, FVector Location, FRotator Rotation);
	void PlaceObjectByType(int32 ObjectId);
	void SetTileLocation(const FVector Location);
	FVector GetTileLocation();
	
	// Egg Operation
	void PlaceEgg(int32 EggId, int32 PlayerId, int32 posX, int32 posY);
	void DestroyEgg(const int32 EggId);
	bool IsEggInArray(int32 EggIdToFind);
	bool IsEggInArray();
	TArray<FEggInfo> GetTileEggInfos();
	FEggInfo *GetEggInfoById(const int32 EggId);
	
	UStaticMeshComponent* TileMesh;
	/*same map object verification*/
	TArray<FString> OldProtocol;
private:
	
	FVector TileLocation;
	UPROPERTY()
	UObjectPathManager* PathManager;
	TArray<FObjectInfo> ObjectOnTile;
	TArray<FEggInfo> EggOnTile;
};
