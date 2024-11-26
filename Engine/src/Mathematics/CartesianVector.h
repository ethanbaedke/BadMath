#pragma once

#include "Math.h"

namespace Lumex {

		/*
		CartesianVector is a Vector that is represented with X, Y, and Z
		*/
		class CartesianVector
		{
		public:
			float X = 0.0f;
			float Y = 0.0f;
			float Z = 0.0f;

			/* Constructors */
			CartesianVector();
			CartesianVector(float x, float y, float z);

			/*
			These calculate the length of the vector
			SquaredMagnitude is much faster and should be used for length comparisons between vectors
			*/
			float Magnitude() const;
			float SquaredMagnitude() const;

			float DotProduct(const CartesianVector& other) const;
			CartesianVector CrossProduct(const CartesianVector& other) const;
			CartesianVector LinearInterpolate(const CartesianVector& other, float percent) const;

			/* Operator overloads */
			CartesianVector operator+(const CartesianVector& other) const;
			CartesianVector operator-(const CartesianVector& other) const;
			CartesianVector operator*(float scalar) const;
			CartesianVector operator/(float scalar) const;
			CartesianVector operator-() const;
		};

		/* Operator overload for multiplication where the scalar is on the left */
		CartesianVector operator*(float scalar, const CartesianVector& cv);

}