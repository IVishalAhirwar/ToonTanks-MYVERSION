//Copyright©2021 vAhirwar Technology.All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"
class AProjectileBase;
UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnBase();
	virtual void HandleDestruction();
private:
UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components",meta=(AllowPrivateAccess = "true"))
	class UCapsuleComponent* Capsule;
	
UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components",meta=(AllowPrivateAccess = "true"))
    UStaticMeshComponent* BaseMesh;
	
UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components",meta=(AllowPrivateAccess = "true"))
    UStaticMeshComponent* TurretMesh;
	
UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components",meta=(AllowPrivateAccess = "true"))	
    USceneComponent* ProjectileSpawnPoint;

UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Components",meta=(AllowPrivateAccess = "true"))	
	class UHealthComponent* HealthComponentRef;

UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category ="Projectiles!",meta =(AllowPrivateAccess =true))
	TSubclassOf<AProjectileBase>ProjectileClass;

UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category ="Effects",meta =(AllowPrivateAccess =true))
	UParticleSystem* DeathParticle;

UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category =" Sound Effects",meta= (AllowPrivateAccess =true))
	USoundBase* DeathSound;

UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category ="Camera Shake Effects",meta= (AllowPrivateAccess =true))
	TSubclassOf<UCameraShake>DeathShake;






protected:
void RotateTurret(FVector LookAtTarget);
void Fire();

};
