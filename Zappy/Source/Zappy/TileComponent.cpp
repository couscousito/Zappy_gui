// Fill out your copyright notice in the Description page of Project Settings.


#include "TileComponent.h"

// Sets default values
ATileComponent::ATileComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PathManager = NewObject<UObjectPathManager>();
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	RootComponent = TileMesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TileMeshAsset(TEXT("/Game/StarterContent/Architecture/Floor_400x400.Floor_400x400"));
	if (TileMeshAsset.Succeeded())
	{
		TileMesh->SetStaticMesh(TileMeshAsset.Object);
	}
}

void ATileComponent::PlaceObject(const FString PathToObject, FVector Location, FRotator Rotation)
{
	UStaticMesh* MeshToPlace = LoadObject<UStaticMesh>(nullptr, *PathToObject);
	;
	if (!MeshToPlace)
	{
		UE_LOG(LogTemp, Warning, TEXT("PathToObject: Object path is invalid."));
		return;
	}
	
	float TargetXY = 40.0f;
	FVector mesh = MeshToPlace->GetBounds().BoxExtent * 2;
	float MaxXY = FMath::Max(mesh.X, mesh.Y);
	const FVector ScaleFactor = FVector(TargetXY / MaxXY);
	
	const FVector WorldLocation = TileLocation + Location;
	UStaticMeshComponent* NewMeshComponent = NewObject<UStaticMeshComponent>(this);
	if (NewMeshComponent)
	{
		NewMeshComponent->SetStaticMesh(MeshToPlace);
		NewMeshComponent->SetWorldLocation(WorldLocation);
		NewMeshComponent->SetWorldRotation(Rotation);
		NewMeshComponent->SetWorldScale3D(ScaleFactor);
		NewMeshComponent->RegisterComponent();
		NewMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	}
}

bool ATileComponent::AreTMapIdentical(const TMap<EObjectType, int32>& Map1, const TMap<EObjectType, int32>& Map2)
{
	if (Map1.Num() != Map2.Num())
	{
		return false;
	}

	for (const auto& Pair : Map1)
	{
		const int32* ValueInMap2 = Map2.Find(Pair.Key);
		if (!ValueInMap2 || *ValueInMap2 != Pair.Value)
		{
			return false;
		}
	}
	return true;
}

void ATileComponent::PlaceObjectList(TMap<EObjectType, int32> ObjectList)
{
	if (AreTMapIdentical(ObjectList, ObjectOnTile))
	{
		return;
	}
	ObjectOnTile = ObjectList;
	for (auto El: ObjectList)
	{
		for (int32 i = 0; i < El.Value; i++)
		{
			FVector Location(FMath::RandRange(0.0f, 400.0f), FMath::RandRange(0.0f, 400.0f), 0.0f);
			FRotator Rotation = FRotator::ZeroRotator;
			PlaceObject(PathManager->GetAssetPath(El.Key), Location, Rotation);
		}
	}
}

void ATileComponent::PlaceEgg(int32 EggId, int32 PlayerId, int32 PosX, int32 PosY)
{	
	FEggInfo NewEgg;
	NewEgg.EggId = EggId;
	NewEgg.PlayerID = PlayerId;
	NewEgg.Coordinate.X = PosX;
	NewEgg.Coordinate.Y = PosY;
	
	EggOnTile.Add(NewEgg);
	FVector Location(FMath::RandRange(0.0f, 400.0f), FMath::RandRange(0.0f, 400.0f), 0.0f);
	FRotator Rotation = FRotator::ZeroRotator;
	PlaceObject(PathManager->GetAssetPath(EObjectType::Egg), Location, Rotation);
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

