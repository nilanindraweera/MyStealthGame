// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	InnerSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComp"));
	InnerSphereComponent->SetSphereRadius(200);
	InnerSphereComponent->SetupAttachment(MeshComp);

	OuterSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("OutterSphereComp"));
	OuterSphereComponent->SetSphereRadius(3000);
	OuterSphereComponent->SetupAttachment(MeshComp);
}

void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	InnerSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapInnerSphere);
}

void ABlackHole::OverlapInnerSphere(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherActor)
	{
		otherActor->Destroy();
	}
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlappingComps;
	OuterSphereComponent->GetOverlappingComponents(OverlappingComps);

	for (int32 i = 0; i < OverlappingComps.Num(); i++)
	{
		UPrimitiveComponent* primComp = OverlappingComps[i];
		if (primComp && primComp->IsSimulatingPhysics())
		{
			const float sphereRadius = OuterSphereComponent->GetScaledSphereRadius();
			const float forceStrength = -2000;

			primComp->AddRadialForce(GetActorLocation(), sphereRadius, forceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}

}

