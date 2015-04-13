/*
 * MoveTo.h
 *
 *  Created on: Apr 6, 2015
 *      Author: ceefour
 */

#ifndef SRC_MOVETO_HPP_
#define SRC_MOVETO_HPP_

#include <string>
#include <boost/property_tree/ptree.hpp>

namespace lumen {

class MoveTo {
public:
	MoveTo();
	MoveTo(const boost::property_tree::ptree &pt);
	virtual ~MoveTo();
	std::string str();

	double getBackDistance() const {
		return backDistance;
	}

	void setBackDistance(double backDistance) {
		this->backDistance = backDistance;
	}

	double getRightDistance() const {
		return rightDistance;
	}

	void setRightDistance(double rightDistance) {
		this->rightDistance = rightDistance;
	}

	double getTurnCcwDeg() const {
		return turnCcwDeg;
	}

	void setTurnCcwDeg(double turnCcwDeg) {
		this->turnCcwDeg = turnCcwDeg;
	}

private:
	double backDistance;
	double rightDistance;
	double turnCcwDeg;
};

} /* namespace lumen */

#endif /* SRC_MOVETO_HPP_ */
