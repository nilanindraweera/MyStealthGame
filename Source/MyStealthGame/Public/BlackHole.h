// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHole.generated.h"

class USphereComponent;

UCLASS()
class MYSTEALTHGAME_API ABlackHole : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category="Components")
	USphereComponent* InnerSphereComponent;

	UPROPERTY(VisibleAnywhere, Category="Components")
	USphereComponent* OuterSphereComponent;


	void BeginPlay() override;

protected:
	UFUNCTION()
	void OverlapInnerSphere(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComponent,
			int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

public:	
	ABlackHole();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
