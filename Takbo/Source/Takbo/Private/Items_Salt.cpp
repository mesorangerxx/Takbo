// Fill out your copyright notice in the Description page of Project Settings.


#include "Items_Salt.h"

// Sets default values
AItems_Salt::AItems_Salt()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentQuantity = 0;
	MaxMass = 100;
	MinMass = 0;

	RunningTime = 0.f;
	Amplitude = 1.f;
	Oscillations = 1.f;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	RootComponent = StaticMesh;

}

// Called when the game starts or when spawned
void AItems_Salt::BeginPlay()
{
	Super::BeginPlay();

	SetMass();
	SetScale();
}

int32 AItems_Salt::GetRandomMass()
{
	return CurrentQuantity;
}

void AItems_Salt::SetMass()
{
	CurrentQuantity = FMath::Abs(FMath::RandRange(MinMass, MaxMass));
}

void AItems_Salt::SetScale()
{
	StaticMesh->GetRelativeTransform().SetScale3D(FVector(GetActorScale3D().X * CurrentQuantity, GetActorScale3D().Y * CurrentQuantity, GetActorScale3D().Z * CurrentQuantity));
}

// Called every frame
void AItems_Salt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	StaticMesh->AddLocalRotation(FRotator(0.f, 1.f, 0.f));

	/** Makes the item oscillate up and down*/
	FVector NewLocation = GetActorLocation();
	NewLocation.Z = NewLocation.Z + (Amplitude)* FMath::Cos((Oscillations)* RunningTime);
	SetActorLocation(NewLocation);
	RunningTime += DeltaTime;
}

