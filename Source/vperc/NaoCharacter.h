// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include <boost/numeric/ublas/vector.hpp>
#include "SimpleAmqpClient/SimpleAmqpClient.h"
#include "Avatar.hpp"
#include "NaoCharacter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogLumen, Log, All);

using namespace boost::numeric;
using namespace AmqpClient;
using namespace lumen;

UCLASS()
class VPERC_API ANaoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANaoCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void onUpdate(double deltaTime/*seconds*/);

private:
	boost::shared_ptr<Avatar> avatar;
	std::string consumer_tag;
	Channel::ptr_t channel;
	bool playing = false;

	// Position animation
	ublas::vector<double> positionDelta;
	/**
	* Intended duration of the animation.
	*/
	double positionDuration = 0.0;
	/**
	* Intended turn (CCW, degrees) of the position animation.
	*/
	double positionTurn = 0.0;
	/**
	* Remaining progress towards end of animation, from 1.0 to 0.0.
	* if > 0 then this will be animated.
	*/
	double positionProgressRemaining = 0.0;

};
