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

UStaticMeshComponent* ATileComponent::PlaceObject(const FString& PathToObject, FVector Location, FRotator Rotation)
{
	UStaticMesh* MeshToPlace = LoadObject<UStaticMesh>(nullptr, *PathToObject);
	;
	if (!MeshToPlace)
	{
		UE_LOG(LogTemp, Warning, TEXT("PathToObject: Object path is invalid."));
		return nullptr;
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
		return NewMeshComponent;
	}
	return nullptr;
}

void ATileComponent::PlaceObjectByType(int32 ObjectId)
{
	FObjectInfo ObjectInfo;
	FVector Location(FMath::RandRange(0.0f, 400.0f), FMath::RandRange(0.0f, 400.0f), 0.0f);
	FRotator Rotation = FRotator::ZeroRotator;
	
	ObjectInfo.ObjectType = static_cast<EObjectType>(ObjectId);
	ObjectInfo.ObjectId = ObjectId;
	ObjectInfo.ObjectMesh = PlaceObject(PathManager->GetAssetPath(static_cast<EObjectType>(ObjectId)), Location, Rotation);
	ObjectOnTile.Add(ObjectInfo);
}

void ATileComponent::PlaceEgg(int32 EggId, int32 PlayerId, int32 PosX, int32 PosY)
{	
	FEggInfo NewEgg;
	FVector Location(FMath::RandRange(0.0f, 400.0f), FMath::RandRange(0.0f, 400.0f), 0.0f);
	FRotator Rotation = FRotator::ZeroRotator;
	
	NewEgg.EggId = EggId;
	NewEgg.PlayerID = PlayerId;
	NewEgg.EggMesh = PlaceObject(PathManager->GetAssetPath(EObjectType::Egg), Location, Rotation);
	EggOnTile.Add(NewEgg);
}

TArray<FEggInfo> ATileComponent::GetTileEggInfos()
{
	return EggOnTile;
}

FEggInfo *ATileComponent::GetEggInfoById(const int32 EggId)
{
	FEggInfo* FoundEgg = EggOnTile.FindByPredicate([EggId](const FEggInfo& Tile)
	{
		return Tile.EggId == EggId;
	});
	return FoundEgg;
}

void ATileComponent::DestroyEgg(const int32 EggId)
{
	UE_LOG(LogTemp, Warning, TEXT("Destroy Egg func"));
	for (int32 Index = 0; Index < EggOnTile.Num(); ++Index)
	{
		if (EggOnTile[Index].EggId == EggId)
		{
			if (EggOnTile[Index].EggMesh != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Destroy Egg succesfully"));
				EggOnTile[Index].EggMesh->DestroyComponent();
				EggOnTile[Index].EggMesh = nullptr; // Optionnel : éviter les références futures invalides
			}

			EggOnTile.RemoveAt(Index);
			return;
		}
	}

}

bool ATileComponent::IsEggInArray(int32 EggIdToFind)
{
	// Utilisation de FindByPredicate pour rechercher un œuf avec le EggId spécifié
	const FEggInfo* FoundEgg = EggOnTile.FindByPredicate([EggIdToFind](const FEggInfo& Egg) {
		return Egg.EggId == EggIdToFind;
	});

	// Retourne true si un œuf est trouvé, sinon retourne false
	return FoundEgg != nullptr;
}

bool ATileComponent::IsEggInArray()
{
	return EggOnTile.Num() != 0;
}


void ATileComponent::SetTileLocation(const FVector Location)
{
	TileLocation = Location;
}

FVector ATileComponent::GetTileLocation()
{
	return TileLocation;
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

