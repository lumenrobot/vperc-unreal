// Fill out your copyright notice in the Description page of Project Settings.

#include "vperc.h"
#include "NaoActor.h"


// Sets default values
ANaoActor::ANaoActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANaoActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANaoActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	UE_LOG(LogTemp, Warning, TEXT("NaoActor Deltatime %s"), DeltaTime);
}

