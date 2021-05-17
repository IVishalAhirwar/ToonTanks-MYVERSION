//Copyright©2021 Vishal Ahirwar. All rights reserved.
#include "Tank.h"
#include"GameFrameWork/SpringArmComponent.h"
#include"Camera/CameraComponent.h"

ATank::ATank()
{
	CameraBoom= CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component."));
	CameraBoom->SetupAttachment(RootComponent);

	Camera =CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component."));
	Camera->SetupAttachment(CameraBoom);

};

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef =Cast<APlayerController>(GetController());
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate();
	Move();
	if(PlayerControllerRef)
	{
		FHitResult TraceHit;
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility,false,TraceHit);
		FVector HitLocation =TraceHit.ImpactPoint;
		RotateTurret(HitLocation);
	};
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward",this,&ATank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn",this,&ATank::CalculateRotation);
	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&ATank::Fire);
}
void ATank::CalculateMoveInput(float Axis)
{
	MoveDirection =FVector(Axis*MoveSpeed*GetWorld()->DeltaTimeSeconds,0.f,0.f);

};
void ATank::CalculateRotation(float Axis)
{
	float RotateAmount =Axis*TurnSpeed*GetWorld()->DeltaTimeSeconds;
	FRotator Rotation =FRotator(0.f,RotateAmount,0.f);
	RotationDirection =FQuat(Rotation);
};
void ATank::Move()
{
	AddActorLocalOffset(MoveDirection,true);
};
void ATank::Rotate()
{
	AddActorLocalRotation(RotationDirection,true);
};

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	bIsPlayerAlive =false;
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	
	//Destroy();

};

bool ATank::GetIsPlayerAlive() const
{
	return bIsPlayerAlive;
};

