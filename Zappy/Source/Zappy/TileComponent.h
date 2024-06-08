// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Containers/Map.h"
#include "TileComponent.generated.h"

UENUM(BlueprintType)
enum class EObjectType : uint8
{
	Food,
	Linemate,
	Deraumere,
	Sibur,
	Mendiane,
	Phiras,
	Thystame,
	Undefine,
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
	void PlaceObject(const TCHAR* PathToObject, FVector Location, FRotator Rotation);
	void PlaceObjectList(TMap<EObjectType, int32> ObjectList);
	void SetTileLocation(const FVector Location);
	UStaticMeshComponent* TileMesh;
private:
	FVector TileLocation;
};
