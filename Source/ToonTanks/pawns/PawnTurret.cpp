
//©vAhirwarTechnology 2021.All rights reerved.

#include "PawnTurret.h"
#include"Kismet/GameplayStatics.h"
#include"Tank.h"

void APawnTurret::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle,this,&APawnTurret::CheckFireCondition,FireRate,true);
    PlayerTank =Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
};
void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if(!PlayerTank||ReturnDistance()>FireRange)
    {
        return;
    }
   RotateTurret(PlayerTank->GetActorLocation());

};

void APawnTurret::CheckFireCondition()
{
    if(!PlayerTank || !PlayerTank->GetIsPlayerAlive())
    {
        return;
    }
    if(ReturnDistance()<=FireRange)
    {
         Fire();
    }else
    {
        UE_LOG(LogTemp,Warning,TEXT("Enemy Outof Range!"));
    };
    
};
float APawnTurret::ReturnDistance()
{
    return FVector::Dist(PlayerTank->GetActorLocation(),GetActorLocation());
};

void APawnTurret::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();

};





