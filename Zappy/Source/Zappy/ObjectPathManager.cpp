// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPathManager.h"

#include "TileComponent.h"

UObjectPathManager::UObjectPathManager()
{
	ObjectPaths.Add(EObjectType::Food, TEXT("/Game/Imported/Food/SM_Food.SM_Food"));
	ObjectPaths.Add(EObjectType::Linemate, TEXT("/Game/Imported/Crystals/Linemate/SM_Linemate.SM_Linemate"));
	ObjectPaths.Add(EObjectType::Deraumere, TEXT("/Game/Imported/Crystals/Deraumere/SM_deraumere.SM_Deraumere"));
	ObjectPaths.Add(EObjectType::Sibur, TEXT("/Game/Imported/Crystals/Sibur/SM_Sibur.SM_Sibur"));
	ObjectPaths.Add(EObjectType::Mendiane, TEXT("/Game/Imported/Crystals/Mendiane/SM_Mendiane.SM_Mendiane"));
	ObjectPaths.Add(EObjectType::Phiras, TEXT("/Game/Imported/Crystals/Phiras/SM_Phiras.SM_Phiras"));
	ObjectPaths.Add(EObjectType::Thystame, TEXT("/Game/Imported/Crystals/Thystame/SM_Thystame.SM_Thystame"));
	ObjectPaths.Add(EObjectType::Egg, TEXT("/Game/Imported/Egg/SM_Egg.SM_Egg"));
}

FString UObjectPathManager::GetAssetPath(EObjectType ObjectType) const
{
	const FString* Path = ObjectPaths.Find(ObjectType);
	return Path ? *Path : FString();
}

