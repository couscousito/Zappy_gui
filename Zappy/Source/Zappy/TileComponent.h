// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Containers/Map.h"
#include "ObjectPathManager.h"
#include "TileComponent.generated.h"

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
	UStaticMeshComponent* TileMesh;
private:
	FVector TileLocation;
	UPROPERTY()
	UObjectPathManager* PathManager;
};
