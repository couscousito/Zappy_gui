// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SkeletonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Charactere mesh"));
	SkeletonMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("/Game/Imported/TileObject/Barbarian_Skeleton.Barbarian_Skeleton"));
	if (SkeletalMeshAsset.Succeeded())
	{
		SkeletonMesh->SetSkeletalMesh(SkeletalMeshAsset.Object);
	}
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Imported/TileObject/Barbarian_PhysicsAsset.Barbarian_PhysicsAsset"));
	if (Material)
	{
		SkeletonMesh->SetMaterial(0, Material);
	}
	
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

