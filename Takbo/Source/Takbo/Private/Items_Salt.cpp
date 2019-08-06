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

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(FName("TriggerBox"));
	RootComponent = TriggerBox;

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	TriggerBox->SetBoxExtent(FVector(62.f, 62.f, 62.f));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AItems_Salt::BeginPlay()
{
	Super::BeginPlay();

	SetMass();
	SetScale();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AItems_Salt::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AItems_Salt::OnvOverlapEnd);
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
	StaticMesh->SetWorldScale3D(FVector((CurrentQuantity/2.f), (CurrentQuantity / 2.f), (CurrentQuantity / 2.f)));
}

void AItems_Salt::OnOverlapBegin(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin."))
	Destroy(); // Destroy this actor
}

void AItems_Salt::OnvOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap End."))
}
