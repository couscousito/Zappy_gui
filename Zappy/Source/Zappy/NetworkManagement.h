// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sockets.h"
#include "Networking.h"
#include "NetworkManagement.generated.h"

/**
 * 
 */

UCLASS()
class ZAPPY_API UNetworkManagement : public UObject
{
	GENERATED_BODY()
public:
	UNetworkManagement();
	bool ConnectToServer(const FString& ServerAddress, const int32 Port);
	void SendDataToServer(const FString& Data) const;
	FString ReceiveData() const;
private:
	FSocket *Socket;
};
