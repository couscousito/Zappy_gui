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

void ATileComponent::PlaceObject(const TCHAR* PathToObject, FVector Location, FRotator Rotation)
{
	UStaticMesh* MeshToPlace = LoadObject<UStaticMesh>(nullptr, PathToObject);
	if (!MeshToPlace)
	{
		UE_LOG(LogTemp, Warning, TEXT("PathToObject: Object path is invalid."));
		return;
	}
	const FVector WorldLocation = TileLocation + Location;
	UStaticMeshComponent* NewMeshComponent = NewObject<UStaticMeshComponent>(this);
	if (NewMeshComponent)
	{
		NewMeshComponent->SetStaticMesh(MeshToPlace);
		NewMeshComponent->SetWorldLocation(WorldLocation);
		NewMeshComponent->SetWorldRotation(Rotation);
		NewMeshComponent->RegisterComponent();
		NewMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void ATileComponent::PlaceObjectList(TMap<EObjectType, int32> ObjectList)
{
	
}


void ATileComponent::SetTileLocation(const FVector Location)
{
	TileLocation = Location;
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

