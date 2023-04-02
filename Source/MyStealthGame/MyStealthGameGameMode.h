// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyStealthGameGameMode.generated.h"

UCLASS(minimalapi)
class AMyStealthGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Specatating")
	TSubclassOf<AActor> MissionEndSpecatotingActor;

public:
	AMyStealthGameGameMode();

	void CompleteMission(APawn* instigatorPawn);

	UFUNCTION(BlueprintImplementableEvent, Category="GameMode")
	void OnMissionCompleted(APawn* instigatorPawn);
};



