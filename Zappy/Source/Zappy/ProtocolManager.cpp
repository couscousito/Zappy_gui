// Fill out your copyright notice in the Description page of Project Settings.


#include "ProtocolManager.h"

// Sets default values
AProtocolManager::AProtocolManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NetworkManagement = NewObject<UNetworkManagement>();
}

void AProtocolManager::InitCommandMap()
{
	CommandMap.Add(TEXT("msz"), [this](const FString &Params) { LaunchMsz(Params); });
	CommandMap.Add(TEXT("bct"), [this](const FString &Params) { LaunchBct(Params); });
	CommandMap.Add(TEXT("enw"), [this](const FString &Params) { LaunchEnw(Params); });
}

void AProtocolManager::InitGameClass()
{
	GameMap = GetWorld()->SpawnActor<AGameMap>(FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator);
}

// Called when the game starts or when spawned
void AProtocolManager::BeginPlay()
{
	Super::BeginPlay();
	InitGameClass();
	InitCommandMap();
	if (NetworkManagement->ConnectToServer(TEXT("127.0.0.1"), 4040))
	{
		NetworkManagement->SendDataToServer(TEXT("GRAPHIC\n"));
	}
}

void AProtocolManager::ParseCommand(const FString &Command)
{
	if (!Command.IsEmpty())
	{
		TArray<FString> ProtocolArray;
		Command.ParseIntoArray(ProtocolArray, TEXT("\n"), true);

		for (auto it : ProtocolArray)
		{
			TArray<FString> SeparateCommand;
			it.ParseIntoArray(SeparateCommand, TEXT(" "), true);
			if (CommandMap.Contains(SeparateCommand[0]))
			{
				CommandMap[SeparateCommand[0]](it);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Error: Unknown Command: %s"), *it);
			}
		}
		// UE_LOG(LogTemp, Warning, TEXT("Data receive by server: %s"), *Command);
	}
}

// Called every frame
void AProtocolManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FString DataReceive = NetworkManagement->ReceiveData();
	// UE_LOG(LogTemp, Warning, TEXT("Data from server: %s"), *DataReceive);
	ParseCommand(DataReceive);
}

/* Command From Server */

void AProtocolManager::LaunchMsz(const FString& Command)
{
	UE_LOG(LogTemp, Warning, TEXT("Enter in commandMap msz"));
	TArray<FString> SeparateCommand;
	Command.ParseIntoArray(SeparateCommand, TEXT(" "), true);
	
	if (GameMap)
	{
		GameMap->InitMap(FCString::Atoi(*SeparateCommand[1]), FCString::Atoi(*SeparateCommand[2]));
		GameMap->GenerateMap();
	}
}

void AProtocolManager::LaunchBct(const FString& Command)
{
	GameMap->SetObjectOnMapByProtocol(Command);
}

void AProtocolManager::LaunchEnw(const FString& Command)
{
	TArray<FString> SeparateCommand;
	Command.ParseIntoArray(SeparateCommand, TEXT(" "), true);
	GameMap->SetEggOnMap(SeparateCommand);
}
