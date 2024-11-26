#include "CylindricalVector.h"

#include <xmmintrin.h>

namespace Lumex {

	CylindricalVector::CylindricalVector()
	{
	}

	CylindricalVector::CylindricalVector(float height, float radius, float theta)
		: Height(height), Radius(radius), Theta(theta)
	{
	}

	CartesianVector CylindricalVector::ToCartesian() const
	{
		float x = Radius * Math::Cos(Theta);
		float z = Radius * Math::Sin(Theta);
		float y = Height;

		CartesianVector resultVec(x, y, z);
			
		return resultVec;
	}

	float CylindricalVector::Magnitude() const
	{
		float sm = SquaredMagnitude();
		float mag = Math::SquareRoot(sm);
		return mag;
	}

	float CylindricalVector::SquaredMagnitude() const
	{
		// Equation = (radius^2 * cos^2(theta)) + (radius^2 * sin^2(theta)) + height^2
		// Get radius^2, height^2, sin^2(theta), and cos^2(theta)
		float sinTheta = Math::Sin(Theta);
		float cosTheta = Math::Cos(Theta);
		__m128 values128 = _mm_set_ps(cosTheta, sinTheta, Height, Radius);
		__m128 squared128 = _mm_mul_ps(values128, values128);
		float squared[4];
		_mm_store_ps(squared, squared128);

		// Calculate equation
		float result = (squared[0] * squared[3]) + (squared[0] * squared[2]) + squared[1];

		return result;
	}

	float CylindricalVector::DotProduct(const CylindricalVector& other) const
	{
		float result = Radius * other.Radius * Math::Cos(Theta - other.Theta) + Height * other.Height;

		return result;
	}

	CylindricalVector CylindricalVector::LinearInterpolate(const CylindricalVector& other, float percent) const
	{
		// Treat both vectors like components of the new vector, with lengths based on the input percent
		CylindricalVector thisComponent = operator*(1.0f - percent);
		CylindricalVector otherComponent = other.operator*(percent);

		// Add these to get the resultent
		CylindricalVector resultVec = thisComponent.operator+(otherComponent);

		return resultVec;
	}

	CylindricalVector CylindricalVector::operator+(const CylindricalVector& other) const
	{
		// radius_x = radius_this * cos(theta_this) + radius_other * cos(theta_other)
		// radius_z = radius_this * sin(theta_this) + radius_other * sin(theta_other)
		// Use register *magic* to make these happen (manipulate the 128 bit register to multiply and add our floats more efficiently)
		__m128 radius128 = _mm_set_ps(Radius, Radius, other.Radius, other.Radius);
		__m128 trig128 = _mm_set_ps(Math::Cos(Theta), Math::Sin(Theta), Math::Cos(other.Theta), Math::Sin(other.Theta));
		__m128 result128 = _mm_mul_ps(radius128, trig128);
		__m128 add128 = _mm_shuffle_ps(result128, result128, _MM_SHUFFLE(1, 0, 0, 0));
		result128 = _mm_add_ps(result128, add128);
		float results[4];
		_mm_store_ps(results, result128);

		// Create the new vector from our results
		float r = Math::SquareRoot(results[3] * results[3] + results[2] * results[2]);
		float theta = Math::Arctan2(results[2], results[3]);
		float h = Height + other.Height;
		CylindricalVector resultVec(h, r, theta);

		return resultVec;
	}

	CylindricalVector CylindricalVector::operator-(const CylindricalVector& other) const
	{
		// Add this vector with the negative of the other vector
		CylindricalVector negOther = other.operator-();
		CylindricalVector resultVec = operator+(negOther);

		return resultVec;
	}

	CylindricalVector CylindricalVector::operator*(float scalar) const
	{
		// If the scalar is positive, scale up the height and radius
		if (scalar > 0)
		{
			CylindricalVector resultVec(Height * scalar, Radius * scalar, Theta);
			return resultVec;
		}
		// If the scalar is negative, scale up the height and radius, but keep the radius positive and instead rotate theta around the vertical axis to get the correct direction
		else
		{
			CylindricalVector resultVec(Height * scalar, Radius * -scalar, Theta - Math::PI);
			return resultVec;
		}
	}

	CylindricalVector CylindricalVector::operator/(float scalar) const
	{
		// Multiply this vector with the inverse of the scalar
		float inverseScalar = 1.0f / scalar;
		CylindricalVector resultVec = operator*(inverseScalar);

		return resultVec;
	}

	CylindricalVector CylindricalVector::operator-() const
	{
		CylindricalVector resultVec(-Height, Radius, Theta - Math::PI);

		return resultVec;
	}

	CylindricalVector operator*(float scalar, const CylindricalVector& cv)
	{
		CylindricalVector resultVec = cv.operator*(scalar);

		return resultVec;
	}

}