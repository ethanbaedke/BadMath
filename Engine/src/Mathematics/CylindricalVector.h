#pragma once

#include "CartesianVector.h"

namespace Lumex {

	/*
	CylindricalVector is a Vector that is represented with Height, Radius, and Theta
	*/
	class CylindricalVector
	{
	public:
		float Height = 0.0f;
		float Radius = 0.0f;
		float Theta = 0.0f;

		/* Constructors */
		CylindricalVector();
		CylindricalVector(float height, float radius, float theta);


		/* Convert the vector into a vector in Cartesian Coordinates */
		CartesianVector ToCartesian() const;

		/*
		These calculate the length of the vector
		SquaredMagnitude is much faster and should be used for length comparisons between vectors
		*/
		float Magnitude() const;
		float SquaredMagnitude() const;

		/* Returns a vector with the same direction as this with length one */
		CylindricalVector Normalized() const;

		float DotProduct(const CylindricalVector& other) const;
		CylindricalVector LinearInterpolate(const CylindricalVector& other, float percent) const;

		/* Operator overloads */
		CylindricalVector operator+(const CylindricalVector& other) const;
		CylindricalVector operator-(const CylindricalVector& other) const;
		CylindricalVector operator*(float scalar) const;
		CylindricalVector operator/(float scalar) const;
		CylindricalVector operator-() const;
	};

	/* Operator overload for multiplication where the scalar is on the left */
	CylindricalVector operator*(float scalar, const CylindricalVector& cv);

}