#pragma once

#include "CartesianVector.h"

namespace Lumex {

	class Quaternion
	{
	public:
		Quaternion();

		/* Takes in a cartesian vector representing the axis to rotate about and the rotation angle */
		Quaternion(const CartesianVector& vector, float theta);

		/* Returns a copy of the input vector rotated by this quaternion */
		CartesianVector ApplyToCartesianVector(const CartesianVector& vector) const;

		/* Operator overloads */
		Quaternion operator*(const Quaternion& other) const;

		/* NOTE: these functions only exist for testing purposes, these should be replaced once a logging system is implemented */
		inline const CartesianVector& GetQv() const { return m_Qv; }
		inline float GetQw() const { return m_Qw; }
	private:
		/* This holds the unit vector to rotate around in quaternion form */
		CartesianVector m_Qv;

		/* This holds the angle of rotation in quaternion form */
		float m_Qw = 0.0f;
	};

}