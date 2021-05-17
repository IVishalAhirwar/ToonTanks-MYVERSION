//Copyright©2021vAhirwar Technology(Vishal Ahirwar)
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	int32 TT =0;
	class ATank* TankRef;
	class APawnTurret* TurretRef;

	void HandleGameStart();
	void HandleGameOver(bool bIsPlayerWon);
	int32 GetTTCount();
	class AvPlayerController* vPlayerControllerRef =nullptr;

public:

	void ActorDead(AActor* DeadActor);

protected:

UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Game Loop")
	int32 StartDelay =4;
	virtual void BeginPlay()override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bIsPlayerWon);
	
};
