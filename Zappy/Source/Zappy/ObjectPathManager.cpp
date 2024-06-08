// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPathManager.h"

#include "TileComponent.h"

UObjectPathManager::UObjectPathManager()
{
	ObjectPaths.Add(EObjectType::Food, TEXT("/Game/Imported/TileObject/wholerHam.wholerHam"));
	ObjectPaths.Add(EObjectType::Linemate, TEXT("/Game/Imported/TileObject/Linemate.Linemate"));
	ObjectPaths.Add(EObjectType::Deraumere, TEXT("/Game/Imported/TileObject/Deraumere.Deraumere"));
	ObjectPaths.Add(EObjectType::Sibur, TEXT("/Game/Imported/TileObject/Sibur.Sibur"));
	ObjectPaths.Add(EObjectType::Mendiane, TEXT("/Game/Imported/TileObject/Mendiane.Mendiane"));
	ObjectPaths.Add(EObjectType::Phiras, TEXT("/Game/Imported/TileObject/Phiras.Phiras"));
	ObjectPaths.Add(EObjectType::Thystame, TEXT("/Game/Imported/TileObject/Thystame.Thystame"));
}

FString UObjectPathManager::GetAssetPath(EObjectType ObjectType) const
{
	const FString* Path = ObjectPaths.Find(ObjectType);
	return Path ? *Path : FString();
}