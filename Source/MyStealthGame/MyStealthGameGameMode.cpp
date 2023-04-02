// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyStealthGameGameMode.h"
#include "MyStealthGameHUD.h"
#include "MyStealthGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>

AMyStealthGameGameMode::AMyStealthGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AMyStealthGameHUD::StaticClass();
}

void AMyStealthGameGameMode::CompleteMission(APawn* instigatorPawn)
{
	if (!instigatorPawn) {
		return;
	}
	instigatorPawn->DisableInput(nullptr);

	if (MissionEndSpecatotingActor)
	{
		APlayerController* pController = Cast<APlayerController>(instigatorPawn->GetController());
		if (pController)
		{
			TArray<AActor*> outputActors;
			UGameplayStatics::GetAllActorsOfClass(this, MissionEndSpecatotingActor, outputActors);
			if (outputActors.Num() > 0)
			{
				AActor* missionEndSpectator = outputActors[0];
				pController->SetViewTargetWithBlend(missionEndSpectator, 0.75f, EViewTargetBlendFunction::VTBlend_Cubic);
			}

		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MissionEndSpecatotingClass is null"));
	}

	OnMissionCompleted(instigatorPawn);
}
