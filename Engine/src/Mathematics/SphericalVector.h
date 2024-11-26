#pragma once

#include "CartesianVector.h"

namespace Lumex {

	/*
	SphericalVector is a Vector that is represented with Radius, Phi, and Theta
	Phi is the vertical angle between 0 and PI
	Theta is the horizontal angle (unbound)
	*/
	class SphericalVector
	{
	public:
		float Radius = 0.0f;
		float Phi = 0.0f;
		float Theta = 0.0f;

		/* Constructors */
		SphericalVector();
		SphericalVector(float radius, float phi, float theta);

		/* Convert the vector into a vector in Cartesian Coordinates */
		CartesianVector ToCartesian() const;

		float DotProduct(const SphericalVector& other) const;
		SphericalVector LinearInterpolate(const SphericalVector& other, float percent) const;

		/* Operator overloads */
		SphericalVector operator+(const SphericalVector& other) const;
		SphericalVector operator-(const SphericalVector& other) const;
		SphericalVector operator*(float scalar) const;
		SphericalVector operator/(float scalar) const;
		SphericalVector operator-() const;
	};

	/* Operator overload for multiplication where the scalar is on the left */
	SphericalVector operator*(float scalar, const SphericalVector& cv);

}