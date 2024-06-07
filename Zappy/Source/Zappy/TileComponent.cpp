// Fill out your copyright notice in the Description page of Project Settings.


#include "TileComponent.h"

// Sets default values
ATileComponent::ATileComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	RootComponent = TileMesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TileMeshAsset(TEXT("/Game/StarterContent/Architecture/Floor_400x400.Floor_400x400"));
	if (TileMeshAsset.Succeeded())
	{
		TileMesh->SetStaticMesh(TileMeshAsset.Object);
	}
}

// Called when the game starts or when spawned
void ATileComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATileComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

