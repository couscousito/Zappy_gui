// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMap.h"

// Sets default values
AGameMap::AGameMap(const int32 SizeXParam, const int32 SizeYParam): SizeX(10), SizeY(10)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGameMap::GenerateMap() const
{
	UE_LOG(LogTemp, Warning, TEXT("Enter in map generator with size %d | %d"), SizeX, SizeY);

	for (int32 x = 0; x < SizeX; x++)
	{
		for (int32 y = 0; y < SizeY; y++)
		{
			FVector Location(x * 100.0f, y * 100.0f, 0.0f);
			FRotator Rotation = FRotator::ZeroRotator	;
			// FActorSpawnParameters SpawnParams;

			ATileComponent *Tile = GetWorld()->SpawnActor<ATileComponent>(ATileComponent::StaticClass(), Location, Rotation);
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

