// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EPickupType : uint8
{
	PT_wood			UMETA(DisplayName = "Wood"),
	PT_bone			UMETA(DisplayName = "Bone")
};

UCLASS()
class UNIONGAME_API APickup : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	EPickupType PickupType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
		bool bIsActive;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pickup")
	class USphereComponent* BaseCollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	class UStaticMeshComponent* PickupMesh;

	// Sets default values for this actor's properties
	APickup();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/** called when something overlaps the actor */
	UFUNCTION()
		void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	float RunningTime;
};
