// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkManagement.h"

UNetworkManagement::UNetworkManagement()
{
	Socket = nullptr;
}

bool UNetworkManagement::ConnectToServer(const FString& ServerAddress, const int32 Port)
{
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	Socket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("default"), false);    

	FIPv4Address Ip;
	FIPv4Address::Parse(ServerAddress, Ip);
	const TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();
	Addr->SetIp(Ip.Value);
	Addr->SetPort(Port);    

	const bool bConnected = Socket->Connect(*Addr);
	if (bConnected) {
		UE_LOG(LogTemp, Warning, TEXT("Connected to server!"));
	} else {
		UE_LOG(LogTemp, Error, TEXT("Failed to connect to server."));
	}
	return bConnected;
}

void UNetworkManagement::SendDataToServer(const FString& Data) const
{
	if (!Socket)
	{
		UE_LOG(LogTemp, Error, TEXT("Error: Socket is not connected"));
		return;
	}

	const FString CharToSend = Data.GetCharArray().GetData();
	const int32 Size = FCString::Strlen(*CharToSend);
	int32 Sent = 0;

	const bool SendSuccess = Socket->Send((uint8*)TCHAR_TO_UTF8(*CharToSend), Size, Sent);
	if (!SendSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("Data %s cannot be send"), *Data)
	}
}

FString UNetworkManagement::ReceiveData() const
{
	if (!Socket) return "";

	TArray<uint8> ReceivedData;
	uint32 Size;
	FString ReceivedString;
    
	while (Socket->HasPendingData(Size))
	{
		ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));

		int32 Read = 0;
		Socket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);

		ReceivedString += FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(ReceivedData.GetData())));
	}
	return ReceivedString;
}


