// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtractionZone.h"
#include "Components/BoxComponent.h"
#include <Components/DecalComponent.h>
#include "../MyStealthGameGameMode.h"
#include "../MyStealthGameCharacter.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AExtractionZone::AExtractionZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f));
	OverlapComp->SetHiddenInGame(false);

	RootComponent = OverlapComp;

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = FVector(200.f, 200.f, 200.f);
	DecalComp->SetupAttachment(OverlapComp);
}

// Called when the game starts or when spawned
void AExtractionZone::BeginPlay()
{
	Super::BeginPlay();
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AExtractionZone::HandleOverlap);
}

void AExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Overlapped with extraction zone!"));
	AMyStealthGameCharacter* myPawn = Cast<AMyStealthGameCharacter>(OtherActor);
	if (!myPawn){
		return;
	}

	if (!myPawn->IsCarryingObject){
		UGameplayStatics::PlaySound2D(this, ObjectMissingSound);
		return;
	}

	AMyStealthGameGameMode* gamemode = Cast<AMyStealthGameGameMode>(GetWorld()->GetAuthGameMode());
	if (!gamemode){
		return;
	}
	gamemode->CompleteMission(myPawn);
	
}

// Called every frame
void AExtractionZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

