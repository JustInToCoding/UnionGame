// Fill out your copyright notice in the Description page of Project Settings.

#include "UnionGame.h"
#include "Pickup.h"


// Sets default values
APickup::APickup(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsActive = true;

	BaseCollisionComponent = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent"));

	RootComponent = BaseCollisionComponent;

	//Create the static mesh component
	PickupMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PickupMesh"));

	//PickupMesh->SetSimulatePhysics(true);

	//attach the static mesh component to the root component
	PickupMesh->AttachTo(RootComponent);
	
	PickupMesh->SetCollisionProfileName("OverlapAll");

	TScriptDelegate<FWeakObjectPtr> delegate = TScriptDelegate<FWeakObjectPtr>();

	delegate.BindUFunction(this, "OnOverlapBegin");

	PickupMesh->OnComponentBeginOverlap.Add(delegate);

	PrimaryActorTick.bCanEverTick = true;
}

void APickup::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroy();
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	//NewLocation.Z += DeltaHeight * 20.0f;       //Scale our height by a factor of 20
	//RunningTime += DeltaTime;
	Value =+ 200.0f;
	SetActorLocation(NewLocation);
}
