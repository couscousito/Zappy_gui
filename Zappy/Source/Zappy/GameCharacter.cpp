// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SkeletonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Charactere mesh"));
	SkeletonMesh->SetupAttachment(RootComponent);

	// static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("/Game/Imported/TileObject/Walking.Walking"));
	// if (SkeletalMeshAsset.Succeeded())
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("skeleton created"));
	// 	SkeletonMesh->SetSkeletalMesh(SkeletalMeshAsset.Object);
	// }
	// static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Game/Imported/TileObject/Walking_PhysicsAsset.Walking_PhysicsAsset"));
	// if (MaterialAsset.Succeeded())
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("mesh created"));
	// 	CharacterMaterial = MaterialAsset.Object;
	// }
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (CharacterMaterial)
	{
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(CharacterMaterial, this);
		GetMesh()->SetMaterial(0, DynamicMaterial);
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

