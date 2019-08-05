// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "PhysicsEngine/BodyInstance.h"
#include "Items_Salt.generated.h"

UCLASS()
class TAKBO_API AItems_Salt : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItems_Salt();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** This generates random quantities for each instance of this item*/
	int32 GetRandomMass();
	
	/** This sets the item's mass*/
	void SetMass();

	void SetScale();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnvOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** Overlap volume for functionality to be triggered */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Floor Switch")
	UBoxComponent* TriggerBox;

	

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Item Properties")
	int32 CurrentQuantity;
	
	UPROPERTY(EditDefaultsOnly, Category = "Item Properties")
	int32 MaxMass;

	UPROPERTY(EditDefaultsOnly, Category = "Item Properties")
	int32 MinMass;

	UPROPERTY(EditAnywhere, Category = "Floater Variables | Wave Parameters")
	float Amplitude;

	UPROPERTY(EditAnywhere, Category = "Floater Variables | Wave Parameters")
	float Oscillations;

	float RunningTime;
};
