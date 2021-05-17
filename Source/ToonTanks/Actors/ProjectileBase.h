//©vAhirwarTechnology.All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()

private:

UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category ="Projectile Component",meta=(AllowPrivateAccess =true))
	class UProjectileMovementComponent* ProjectileMovement;
	
UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Projectile Mesh",meta= (AllowPrivateAccess =true))
	 UStaticMeshComponent* PMesh;

UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="<P>Speed",meta =(AllowPrivateAccess=true))
	float PSpeed =1300.f;

UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category ="Damage!",meta=(AllowPrivateAccess =true));
	TSubclassOf<UDamageType>Damage;

UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category="Damage!",meta =(AllowPrivateAccess=true));
	float DamageAmount=25.f;

UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category ="Effects",meta=(AllowPrivateAccess =true))
	UParticleSystem* HitParticle;

UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category ="Effects",meta= (AllowPrivateAccess =true))
	class UParticleSystemComponent* Trail;

UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category ="Sound Effects",meta= (AllowPrivateAccess =true))
	USoundBase* HitSound;

UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category ="Effects",meta= (AllowPrivateAccess =true))
	USoundBase* LaunchSound;

UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category ="Camera Shake Effects",meta= (AllowPrivateAccess =true))
	TSubclassOf<UCameraShake>HitShake;
	
UFUNCTION()
	void OnHit(UPrimitiveComponent*HitComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse,const FHitResult&Hit);

public:	

	AProjectileBase();

protected:

	virtual void BeginPlay() override;

};
