/*
 * MoveTo.cpp
 *
 *  Created on: Apr 6, 2015
 *      Author: ceefour
 */

#include "vperc.h"
#include <boost/format.hpp>
#include <MoveTo.hpp>

namespace lumen {

MoveTo::MoveTo() {
	backDistance = 0.0;
	rightDistance = 0.0;
	turnCcwDeg = 0.0;
}

MoveTo::MoveTo(const boost::property_tree::ptree& pt) {
	backDistance = pt.get("backDistance", 0.0);
	rightDistance = pt.get("rightDistance", 0.0);
	turnCcwDeg = pt.get("turnCcwDeg", 0.0);
}

MoveTo::~MoveTo() {
}

std::string MoveTo::str() {
	return (boost::format("MoveTo backDistance=%1%m rightDistance=%2%m turnCcwDeg=%3%°")
		% getBackDistance() % getRightDistance() % getTurnCcwDeg()).str();
}

} /* namespace lumen */
