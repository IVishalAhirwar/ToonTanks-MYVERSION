//Copyright©2021 vAhirwar Technology. All rights reserved.


#include "PawnBase.h"
#include"Components/CapsuleComponent.h"
#include"ToonTanks/Components/HealthComponent.h"
#include"ToonTanks/Actors/ProjectileBase.h"
#include"Kismet/GameplayStatics.h"


// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider."));
	RootComponent =Capsule;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh."));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh =CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh."));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point."));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);	

	HealthComponentRef =CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));


}

void APawnBase::RotateTurret(FVector LookAtTarget)
{
	FVector EndLoc =FVector(LookAtTarget.X,LookAtTarget.Y,LookAtTarget.Z);
	FVector StartLoc =TurretMesh->GetComponentLocation();
	FRotator TurretRotation =FVector(EndLoc-StartLoc).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);	
};

void APawnBase::Fire()
{
	if (ProjectileClass)
	{
		FVector SpawnLocation =ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation =ProjectileSpawnPoint->GetComponentRotation();
		AProjectileBase* TBaseClass = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass,SpawnLocation,SpawnRotation);
		TBaseClass->SetOwner(this);
		/* code */
	};	
	UE_LOG(LogTemp,Warning,TEXT("Firing..."))
};

void APawnBase::HandleDestruction()
{
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathShake);
	UGameplayStatics::SpawnEmitterAtLocation(this,DeathParticle,GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this,DeathSound,GetActorLocation());
};




