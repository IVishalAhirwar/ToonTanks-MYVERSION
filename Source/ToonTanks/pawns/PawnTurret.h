//©vAhirwarTechnology 2021.All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

	private:
UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category ="GamePlay",meta= (AllowPrivateAccess =true))
	float FireRate=2.f;
UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category ="GamePlay",meta= (AllowPrivateAccess =true))
	float FireRange=500.f;

	void CheckFireCondition();
	float ReturnDistance();

	FTimerHandle FireRateTimerHandle;
	class ATank* PlayerTank;

	public:
	virtual void Tick(float DeltaTime)override;
	virtual void HandleDestruction()override;

	protected:
	virtual void BeginPlay()override;
	
	
};
