/*
 * JointInterpolateAngle.cpp
 *
 *  Created on: Apr 6, 2015
 *      Author: ceefour
 */

#include "vperc.h"
#include <JointInterpolateAngle.hpp>
#include <boost/format.hpp>

namespace lumen {

JointInterpolateAngle::JointInterpolateAngle() {
}

JointInterpolateAngle::JointInterpolateAngle(
		const boost::property_tree::ptree& pt) {
	jointId = pt.get("jointId", "");
	targetCcwDeg = pt.get("targetCcwDeg", 0.0);
	duration = pt.get("duration", 5.0);
}

JointInterpolateAngle::~JointInterpolateAngle() {
}

std::string JointInterpolateAngle::str() {
	return (boost::format("JointInterpolateAngle jointId=%1% targetCcwDeg=%2%° duration=%3%s")
		% getJointId() % getTargetCcwDeg() % getDuration()).str();
}

} /* namespace lumen */
