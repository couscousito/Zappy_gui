// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPathManager.generated.h"

enum class EObjectType : uint8;

UCLASS()
class ZAPPY_API UObjectPathManager : public UObject
{
	GENERATED_BODY()

public:
	UObjectPathManager();
	
	UFUNCTION(BlueprintCallable, Category = "Object Paths")
	FString GetAssetPath(EObjectType ObjectType) const;

private:
	TMap<EObjectType, FString> ObjectPaths;
};
