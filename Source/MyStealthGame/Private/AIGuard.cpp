// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGuard.h"
#include <Perception/PawnSensingComponent.h>
#include <DrawDebugHelpers.h>

// Sets default values
AAIGuard::AAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
}

// Called when the game starts or when spawned
void AAIGuard::BeginPlay()
{
	Super::BeginPlay();
	//PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AAIGuard::OnNoiseHear);
}

void AAIGuard::OnPawnSeen(APawn* pawn)
{
	DrawDebugSphere(GetWorld(), pawn->GetActorLocation(), 32.f, 12, FColor::Red, false, 10.f);
}

void AAIGuard::OnNoiseHear(APawn* noiseInstigator, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), noiseInstigator->GetActorLocation(), 32.f, 12, FColor::Cyan, false, 10.f);
}

// Called every frame
void AAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIGuard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

