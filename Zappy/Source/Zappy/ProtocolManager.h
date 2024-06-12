// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMap.h"
#include "GameFramework/Actor.h"
#include "NetworkManagement.h"
#include "ProtocolManager.generated.h"

UCLASS()
class ZAPPY_API AProtocolManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProtocolManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ParseCommand(const FString &Command);
	
	/* -- Game Class Management -- */
private:
	void InitGameClass();
	UPROPERTY()
	UNetworkManagement *NetworkManagement;
	UPROPERTY()
	AGameMap *GameMap;
	
	/* Game Property*/
private:
	TArray<FString> TeamNameArray;
	int32 TimeUnit;
	/* -- Server Command -- */
private:
	TMap<FString, TFunction<void(const FString&)>> CommandMap;
	void InitCommandMap();
	void LaunchMsz(const FString& Command);
	void LaunchBct(const FString& Command);
	void LaunchEnw(const FString& Command);
	void LaunchEdi(const FString& Command);
	void LaunchTna(const FString& Command);
	void LaunchPnw(const FString& Command);
	void LaunchSgt(const FString& Command);
};
