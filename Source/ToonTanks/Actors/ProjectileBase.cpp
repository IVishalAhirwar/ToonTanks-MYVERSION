//©vAhirwarTechnology.All rights reserved.


#include "ProjectileBase.h"
#include"Kismet/GameplayStatics.h"
#include"Components/StaticMeshComponent.h"
#include"Particles/ParticleSystemComponent.h"
#include"GameFrameWork/ProjectileMovementComponent.h"




// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PMesh =CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh!"));
	PMesh->OnComponentHit.AddDynamic(this,&AProjectileBase::OnHit);
	RootComponent =PMesh;
	ProjectileMovement =CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component!"));
	ProjectileMovement->InitialSpeed =PSpeed;
	ProjectileMovement->MaxSpeed =PSpeed*5.f;
	InitialLifeSpan =3.f;

	Trail =CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Traill <Particle System Component>"));
	Trail->SetupAttachment(RootComponent);
	
	
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::PlaySoundAtLocation(this,LaunchSound,GetActorLocation());
	
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse,const FHitResult& Hit)
{
	AActor* MyOwner =GetOwner();
	if(!MyOwner)return;
	
	if(OtherActor && OtherActor!=this &&OtherActor!=MyOwner)
	{
		//UGamePlayStatics::ApplyDamage(OtherActor,DamageAmount,MyOwner->GetInstigatorController(),this,Damage);
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);
		UGameplayStatics::SpawnEmitterAtLocation(this,HitParticle,GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this,HitSound,GetActorLocation());
		UGameplayStatics::ApplyDamage(OtherActor,DamageAmount,MyOwner->GetInstigatorController(),this,Damage);
		Destroy();
	};

};


