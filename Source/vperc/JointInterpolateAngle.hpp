/*
 * JointInterpolateAngle.h
 *
 *  Created on: Apr 6, 2015
 *      Author: ceefour
 */

#ifndef SRC_JOINTINTERPOLATEANGLE_HPP_
#define SRC_JOINTINTERPOLATEANGLE_HPP_

#include <string>
#include <boost/property_tree/ptree.hpp>

namespace lumen {

class JointInterpolateAngle {
public:
	JointInterpolateAngle();
	JointInterpolateAngle(const boost::property_tree::ptree &pt);
	virtual ~JointInterpolateAngle();
	std::string str();

	double getDuration() const {
		return duration;
	}

	void setDuration(double duration) {
		this->duration = duration;
	}

	const std::string& getJointId() const {
		return jointId;
	}

	void setJointId(const std::string& jointId) {
		this->jointId = jointId;
	}

	double getTargetCcwDeg() const {
		return targetCcwDeg;
	}

	void setTargetCcwDeg(double targetCcwDeg) {
		this->targetCcwDeg = targetCcwDeg;
	}

private:
	std::string jointId = "";
	double targetCcwDeg = 0.0;
	double duration = 5.0;
};

} /* namespace lumen */

#endif /* SRC_JOINTINTERPOLATEANGLE_HPP_ */
