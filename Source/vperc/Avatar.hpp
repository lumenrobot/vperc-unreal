/*
 * Avatar.hpp
 *
 *  Created on: Apr 6, 2015
 *      Author: ceefour
 */

#ifndef SRC_AVATAR_HPP_
#define SRC_AVATAR_HPP_

#include <string>
#include <ostream>
#include <boost/numeric/ublas/vector.hpp>

namespace lumen {

using namespace boost::numeric::ublas;

class Avatar {
public:
	Avatar();
	virtual ~Avatar();

	std::string str() const;

	double getHeadPitch() const {
		return headPitch;
	}

	void setHeadPitch(double headPitch) {
		this->headPitch = headPitch;
	}

	double getHeadYaw() const {
		return headYaw;
	}

	void setHeadYaw(double headYaw) {
		this->headYaw = headYaw;
	}

	/**
	 * Position of the center of the base (can be feet, but can be bottoms, or else, depending on pose) of avatar.
	 */
	const vector<double>& getTilePosition() const {
		return tilePosition;
	}

	void setTilePosition(
			const vector<double>& tilePosition = vector<double>(3)) {
		this->tilePosition = tilePosition;
	}

	/**
	 * Position of center eye, relative to tile origin.
	 */
	const vector<double> getCenterEyePosition() const;

	/**
	 * OpenStreetMap tile X, for the current zoom.
	 */
	int getTileX() const {
		return tileX;
	}

	void setTileX(int tileX) {
		this->tileX = tileX;
	}

	/**
	 * OpenStreetMap tile, for the current zoom.
	 */
	int getTileY() const {
		return tileY;
	}

	void setTileY(int tileY) {
		this->tileY = tileY;
	}

	/**
	 * OpenStreetMap zoom level for current local view,
	 * from 0 to 18.
	 */
	int getTileZoom() const {
		return tileZoom;
	}

	void setTileZoom(int tileZoom) {
		this->tileZoom = tileZoom;
	}

	/**
	 * pitch, yaw, and roll; CCW, in degrees.
	 */
	const vector<double>& getRotation() const {
		return rotation;
	}

	void setRotation(const vector<double>& rotation = vector<double>(3)) {
		this->rotation = rotation;
	}

private:
	int tileZoom = 18;
	int tileX = 1;
	int tileY = 1;
	vector<double> tilePosition = vector<double>(3);
	vector<double> rotation = vector<double>(3);
	double headYaw = 0.0;
	double headPitch = 0.0;
};

} /* namespace lumen */

#endif /* SRC_AVATAR_HPP_ */
