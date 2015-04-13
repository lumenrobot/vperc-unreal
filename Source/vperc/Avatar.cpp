/*
 * Avatar.cpp
 *
 *  Created on: Apr 6, 2015
 *      Author: ceefour
 */

#include "vperc.h"
#include <Avatar.hpp>
#include <boost/format.hpp>

namespace lumen {

Avatar::Avatar() {
	tilePosition[0] = 0.0;
	tilePosition[1] = 0.0;
	tilePosition[2] = 0.0;
	rotation[0] = 0.0;
	rotation[1] = 0.0;
	rotation[2] = 0.0;
}

Avatar::~Avatar() {
}

std::string Avatar::str() const {
	return (boost::format("Avatar tile=%1%(%2%,%3%) tilePosition=%4%m,%5%m,%6%m rotation=%7%°,%8%°,%9%° headYaw=%10%° headPitch=%11%° centerEye=%12%m,%13%m,%14%m") %
		getTileZoom() % getTileX() % getTileY() % getTilePosition()[0] % getTilePosition()[1] % getTilePosition()[2] %
		getRotation()[0] % getRotation()[1] % getRotation()[2] % getHeadYaw() % getHeadPitch() %
		getCenterEyePosition()[0] % getCenterEyePosition()[1] % getCenterEyePosition()[2] ).str();
}

const vector<double> Avatar::getCenterEyePosition() const {
	vector<double> headPos(getTilePosition());
	// NAO center eye is 524mm above the base
	// see http://doc.aldebaran.com/1-14/family/nao_h25/dimensions_h25.html
	headPos[1] += 0.524;
	return headPos;
}

} /* namespace lumen */
