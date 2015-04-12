// Fill out your copyright notice in the Description page of Project Settings.

#include "vperc.h"
#include "NaoCharacter.h"


// Sets default values
ANaoCharacter::ANaoCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANaoCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANaoCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//UE_LOG(LogTemp, Warning, TEXT("NaoCharacter Deltatime %s"), DeltaTime);
	FVector cur = GetActorLocation();
	SetActorLocation(FVector(cur.X, cur.Y + 10 * DeltaTime, cur.Z));
}

// Called to bind functionality to input
void ANaoCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

