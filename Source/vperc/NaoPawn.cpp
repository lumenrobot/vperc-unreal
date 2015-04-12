// Fill out your copyright notice in the Description page of Project Settings.

#include "vperc.h"
#include "NaoPawn.h"


// Sets default values
ANaoPawn::ANaoPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANaoPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANaoPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	UE_LOG(LogTemp, Warning, TEXT("NaoPawn Deltatime %s"), DeltaTime);
	SetActorRelativeLocation(FVector(0.1 * DeltaTime, 0.0, 0.0));
}

// Called to bind functionality to input
void ANaoPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

