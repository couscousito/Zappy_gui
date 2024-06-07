// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileComponent.h"
#include "GameMap.generated.h"

UCLASS()
class ZAPPY_API AGameMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameMap(const int32 SizeXParam, const int32 SizeYParam);
	AGameMap() : SizeX(0), SizeY(0){};
	void InitMap(const int32 SizeXParam, const int32 SizeYParam);
	void GenerateMap() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	int32 SizeX;
	int32 SizeY;
};
