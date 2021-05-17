//Copyright©2021vAhirwar Technology(Vishal Ahirwar)


#include "TankGameModeBase.h"
#include"ToonTanks/pawns/Tank.h"
#include"Kismet/GameplayStatics.h"
#include"ToonTanks/PlayerControllers/vPlayerController.h"
#include"ToonTanks/pawns/PawnTurret.h"

void ATankGameModeBase::BeginPlay()
{

    Super::BeginPlay();
    HandleGameStart();
};


void ATankGameModeBase::HandleGameStart()
{
    TT =GetTTCount();    
    TankRef =Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
    vPlayerControllerRef =Cast<AvPlayerController>(UGameplayStatics::GetPlayerController(this,0));
    GameStart();
    if(vPlayerControllerRef){
        vPlayerControllerRef->SetPlayerEnabledState(false);
        FTimerHandle PlayerInputHandle;
        FTimerDelegate PlayerInputDelegate =FTimerDelegate::CreateUObject(vPlayerControllerRef,&AvPlayerController::SetPlayerEnabledState,true);

        GetWorld()->GetTimerManager().SetTimer(PlayerInputHandle,PlayerInputDelegate,StartDelay,false);
        
    };
};

void ATankGameModeBase::HandleGameOver(bool bIsPlayerWon)
{

    GameOver(bIsPlayerWon);

};

int32 ATankGameModeBase::GetTTCount() 
{
    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(),APawnTurret::StaticClass(),TurretActors);
    return TurretActors.Num();
    
};

void ATankGameModeBase::ActorDead(AActor* DeadActor)
{
    //APawnTurret* DestroyedActor =nullptr;
    if(DeadActor==TankRef)
    {
        TankRef->HandleDestruction();
        HandleGameOver(false);

        if(vPlayerControllerRef)
        {
            vPlayerControllerRef->SetPlayerEnabledState(false);

        }
    }
    else if(APawnTurret* DestroyedActor = Cast<APawnTurret>(DeadActor))
    {
       DestroyedActor->HandleDestruction();
       UE_LOG(LogTemp,Warning,TEXT("You Killed: <%s>\n Total Killed :%i"),*DestroyedActor->GetName(),TT); 
        if(--TT <=0)
        {
            HandleGameOver(true);
            UE_LOG(LogTemp,Error,TEXT("You Killed: <%s>\n Total Killed :%i"),*DestroyedActor->GetName(),TT);    
        };

    };
    UE_LOG(LogTemp,Error,TEXT("A Pawn Name<%s> has been dead!"),*DeadActor->GetName());
};


