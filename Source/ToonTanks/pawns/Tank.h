//Copyright©2021 Vishal Ahirwar. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public APawnBase
{
	GENERATED_BODY()

	public:
	bool GetIsPlayerAlive()const;
	ATank();
	virtual void HandleDestruction()override;

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	private:
UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category ="Components",meta =(AllowPrivateAccess ="true"))
	class USpringArmComponent* CameraBoom;
	
UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category ="Components",meta =(AllowPrivateAccess ="true"))	
	class UCameraComponent* Camera;

	FVector MoveDirection;
	FQuat RotationDirection;
	APlayerController* PlayerControllerRef;

	bool bIsPlayerAlive=true;


UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category= "GamePlay", meta =(AllowPrivateAccess ="true"))
	float MoveSpeed = 100.f;

UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "GamePlay", meta =(AllowPrivateAccess ="true"))
	float TurnSpeed = 100.f;

	void CalculateMoveInput(float Axis);
	void CalculateRotation(float Axis);

	void Move();
	void Rotate();
	
	

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
