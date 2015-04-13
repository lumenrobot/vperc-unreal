// Fill out your copyright notice in the Description page of Project Settings.

#include "vperc.h"
#include "NaoCharacter.h"

#include <string>
#include <exception>
#include <boost/format.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/numeric/ublas/vector.hpp>
//#include <boost/thread/thread.hpp>
#include <JointInterpolateAngle.hpp>
#include <MoveTo.hpp>
#include <Avatar.hpp>

using namespace std;
using namespace boost::numeric;
using namespace lumen;

DEFINE_LOG_CATEGORY(LogLumen);

void ANaoCharacter::onUpdate(double deltaTime/*seconds*/) {
	if (positionProgressRemaining > 0.0) {
		double deltaProgress = min(deltaTime / positionDuration, positionProgressRemaining);
		ublas::vector<double> newPos(avatar->getTilePosition());
		newPos[0] += positionDelta[0] * deltaProgress;
		newPos[1] += positionDelta[1] * deltaProgress;
		newPos[2] += positionDelta[2] * deltaProgress;
		avatar->setTilePosition(newPos);
		double deltaTurn = deltaProgress * positionTurn;
		ublas::vector<double> newRot(avatar->getRotation());
		newRot[1] += deltaTurn; // yaw CCW
		if (newRot[1] < -180.0) {
			newRot[1] += 360.0;
		}
		if (newRot[1] > 180.0) {
			newRot[1] -= 360;
		}
		avatar->setRotation(newRot);
		positionProgressRemaining = max(positionProgressRemaining - deltaProgress, 0.0);
	}
}

// Sets default values
ANaoCharacter::ANaoCharacter() : avatar(new Avatar()),
	positionDelta(3)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANaoCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	using boost::property_tree::ptree;
	ptree pt;
	pt.put("Halo", "juga");
	stringstream ss;
	boost::property_tree::json_parser::write_json(ss, pt, true);
	string jsonStr = ss.str();
	//cout << "JSON: " << jsonStr << endl;

	UE_LOG(LogLumen, Log, TEXT("JSON: %s"), *FString(jsonStr.c_str()));

	std::string amqpUri("amqp://localhost");// "amqp://guest:guest@localhost/%2F";
	UE_LOG(LogLumen, Log, TEXT("Connecting AMQP '%s'..."), *FString(amqpUri.c_str()));
	try {
		// IMPORTANT: You *MUST* compile SimpleAmqpClient as release, then put the mt (without gd) version of boost system + chrono in Binaries/Win64
		// otherwise you'll get corrupted std::string. ~Hendy
		channel = Channel::CreateFromUri(amqpUri);

	//	string queue = channel->DeclareQueue("");
	//	UE_LOG(LogLumen, Log, TEXT("Publishing to '%s'..."), *FString(queue.c_str()));
	//	BasicMessage::ptr_t message = BasicMessage::Create("wah keren");
	//	channel->BasicPublish("", queue, message);

	//	string avatarCommandQueue;
	//	channel->DeclareQueue(avatarCommandQueue);
	//	UE_LOG(LogLumen, Log, TEXT("Declared queue '%s'"), *FString(avatarCommandQueue.c_str()));
	//	string topic = "amq.topic";
	//	string avatarCommandKey = "avatar.NAO.command";
	//	channel->BindQueue(avatarCommandQueue, topic, avatarCommandKey);
	//	consumer_tag = channel->BasicConsume(avatarCommandQueue, "");
	//	UE_LOG(LogLumen, Log, TEXT("Consuming %s (topic=%s routing=%s) ..."),
	//		*FString(consumer_tag.c_str()), *FString(topic.c_str()), *FString(avatarCommandKey.c_str()));
	//	
	//	//playing = true;
	}
	catch (const std::exception &e) {
		UE_LOG(LogLumen, Error, TEXT("Error: %s"), *FString(e.what()));
	}
}

// Called every frame
void ANaoCharacter::Tick( float DeltaTime )
{
	using boost::property_tree::ptree;

	Super::Tick(DeltaTime);

	//UE_LOG(LogLumen, Log, TEXT("NaoCharacter Deltatime %f"), DeltaTime);
	UE_LOG(LogLumen, Log, TEXT("NaoCharacter Avatar %s"), *FString(avatar->str().c_str()));
	FVector cur = GetActorLocation();
	SetActorLocation(FVector(cur.X, cur.Y + 10 * DeltaTime, cur.Z));

	if (playing) {
		Envelope::ptr_t envelope(NULL);
		if (channel->BasicConsumeMessage(consumer_tag, envelope, 0)) {
			BasicMessage::ptr_t msg = envelope->Message();
			UE_LOG(LogLumen, Log, TEXT("NaoCharacter %s"), *FString((boost::format("Got message: id=%1% appId=%2% correlationId=%3% contentType=%4% replyTo=%5% body=%6%") %
				msg->MessageId() % msg->AppId() % msg->CorrelationId() % msg->ContentType() % msg->ReplyTo() % msg->Body()).str().c_str()));
			for (auto& entry : msg->HeaderTable()) {
				//UE_LOG(LogLumen, Log, *FString((boost::format("%1% = %2% (%3%)") % entry.first % entry.second.GetString() % entry.second.GetType()).str().c_str()));
				UE_LOG(LogLumen, Log, TEXT("NaoCharacter %s"), *FString(
					(boost::format("%1% = %2% (%3%)") % entry.first % entry.second.GetString() % entry.second.GetType()).str().c_str()));
			}
			ptree inpt;
			istringstream bodyStream(msg->Body());
			boost::property_tree::read_json(bodyStream, inpt);
			for (auto& entry : inpt) {
				UE_LOG(LogLumen, Log, TEXT("NaoCharacter %s"), *FString(
					(boost::format("%1% = %2%") % entry.first % entry.second.get_value("")).str().c_str()));
			}

			string clazz = inpt.get("@type", "");
			if (clazz == "MoveTo") {
				MoveTo moveTo = MoveTo(inpt);
				UE_LOG(LogLumen, Log, TEXT("MoveTo object: %s"), *FString(moveTo.str().c_str()));

				positionDelta[0] = moveTo.getRightDistance(); // right is x+ axis
				positionDelta[1] = 0;
				positionDelta[2] = moveTo.getBackDistance(); // back is z+ axis
				const double moveSpeed = 0.1; // 0.1 m/s
				positionDuration = std::abs(moveTo.getRightDistance()) + std::abs(moveTo.getBackDistance()) / moveSpeed;
				positionTurn = moveTo.getTurnCcwDeg();
				positionProgressRemaining = 1.0;

				//				boost::numeric::ublas::vector<double> newPos(avatar->getTilePosition());
				//				newPos[0] += moveTo.getRightDistance(); // right is x+ axis
				//				newPos[2] += moveTo.getBackDistance(); // back is z+ axis
				//				avatar->setTilePosition(newPos);
			}
			else if (clazz == "JointInterpolateAngle") {
				JointInterpolateAngle obj = JointInterpolateAngle(inpt);
				UE_LOG(LogLumen, Log, TEXT("Message object: %s"), *FString(obj.str().c_str()));
				if (obj.getJointId() == "HeadYaw") {
					avatar->setHeadYaw(obj.getTargetCcwDeg());
				}
				else if (obj.getJointId() == "HeadPitch") {
					avatar->setHeadPitch(obj.getTargetCcwDeg());
				}
			}

			//channel->BasicAck(envelope);
		}
		else {
			//cout << "No message" << endl;
		}

		//onUpdate(DeltaTime);
	}
}

// Called to bind functionality to input
void ANaoCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

