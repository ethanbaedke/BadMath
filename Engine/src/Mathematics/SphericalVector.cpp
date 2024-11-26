#include "SphericalVector.h"

#include <xmmintrin.h>

namespace Lumex {

	Lumex::SphericalVector::SphericalVector()
	{
	}

	SphericalVector::SphericalVector(float radius, float phi, float theta)
		: Radius(radius), Phi(phi), Theta(theta)
	{
	}

	CartesianVector SphericalVector::ToCartesian() const
	{
		float sinPhi = Math::Sin(Phi);
		float cosPhi = Math::Cos(Phi);
		float sinTheta = Math::Sin(Theta);
		float cosTheta = Math::Cos(Theta);

		// x = radius * sin(phi) * cos(theta)
		// z = radius * sin(phi) * sin(theta)
		// y = radius * cos(phi)
		__m128 radius128 = _mm_set_ps(Radius, Radius, Radius, 0.0f);
		__m128 phiTrig128 = _mm_set_ps(sinPhi, sinPhi, cosPhi, 0.0f);
		__m128 thetaTrig128 = _mm_set_ps(cosTheta, sinTheta, 1.0f, 0.0f);
		__m128 mul128 = _mm_mul_ps(radius128, phiTrig128);
		mul128 = _mm_mul_ps(mul128, thetaTrig128);
		float results[4];
		_mm_store_ps(results, mul128);

		// Create the cartesion vector with the converted results
		CartesianVector resultVec(results[3], results[2], results[1]);

		return resultVec;
	}

	float SphericalVector::DotProduct(const SphericalVector& other) const
	{
		// Yes we are getting sine and cosine of both angles for both vectors, we will use all of them
		float sinPhi_this = Math::Sin(Phi);
		float sinPhi_other = Math::Sin(other.Phi);
		float cosPhi_this = Math::Cos(Phi);
		float cosPhi_other = Math::Cos(other.Phi);
		float sinTheta_this = Math::Sin(Theta);
		float sinTheta_other = Math::Sin(other.Theta);
		float cosTheta_this = Math::Cos(Theta);
		float cosTheta_other = Math::Cos(other.Theta);

		// Convert to cartesian coordinates and use these to calculate the new spherical coordinates
		// x = radius * sin(phi) * cos(theta)
		// z = radius * sin(phi) * sin(theta)
		// y = radius * cos(phi)
		// dotProduct = (x1 * x2) + (y1 * y2) + (z1 * z2)
		__m128 radius128 = _mm_set_ps(Radius, other.Radius, Radius, other.Radius);
		__m128 phiTrig128 = _mm_set_ps(sinPhi_this, sinPhi_other, sinPhi_this, sinPhi_other);
		__m128 thetaTrig128 = _mm_set_ps(cosTheta_this, cosTheta_other, sinTheta_this, sinTheta_other);
		__m128 mul128 = _mm_mul_ps(radius128, phiTrig128);
		mul128 = _mm_mul_ps(mul128, thetaTrig128);
		__m128 phiTrigCont128 = _mm_set_ps(cosPhi_this, cosPhi_other, 0.0f, 0.0f);
		__m128 mulCont128 = _mm_mul_ps(radius128, phiTrigCont128);
		__m128 mulA128 = _mm_shuffle_ps(mulCont128, mul128, _MM_SHUFFLE(3, 1, 3, 0));
		__m128 mulB128 = _mm_shuffle_ps(mulCont128, mul128, _MM_SHUFFLE(2, 0, 2, 0));
		__m128 cartesian128 = _mm_mul_ps(mulA128, mulB128);
		float cartesianResults[4];
		_mm_store_ps(cartesianResults, cartesian128);

		float value = cartesianResults[3] + cartesianResults[2] + cartesianResults[1];

		return value;
	}

	SphericalVector SphericalVector::LinearInterpolate(const SphericalVector& other, float percent) const
	{
		// Treat both vectors like components of the new vector, with lengths based on the input percent
		SphericalVector thisComponent = operator*(1.0f - percent);
		SphericalVector otherComponent = other.operator*(percent);

		// Add these to get the resultent
		SphericalVector resultVec = thisComponent.operator+(otherComponent);

		return resultVec;
	}

	SphericalVector SphericalVector::operator+(const SphericalVector& other) const
	{
		// Yes we are getting sine and cosine of both angles for both vectors, we will use all of them
		float sinPhi_this = Math::Sin(Phi);
		float sinPhi_other = Math::Sin(other.Phi);
		float cosPhi_this = Math::Cos(Phi);
		float cosPhi_other = Math::Cos(other.Phi);
		float sinTheta_this = Math::Sin(Theta);
		float sinTheta_other = Math::Sin(other.Theta);
		float cosTheta_this = Math::Cos(Theta);
		float cosTheta_other = Math::Cos(other.Theta);

		// Convert to cartesian coordinates and use these to calculate the new spherical coordinates
		// x = radius * sin(phi) * cos(theta)
		// z = radius * sin(phi) * sin(theta)
		// y = radius * cos(phi)
		// newRadius = sqrt((x1 + x2)^2 + (y1 + y2)^2 + (z1 + z2)^2)
		// newPhi = arccos((y1 + y2) / newRadius)
		// newTheta = arctan2(z1 + z2, x1 + x2)
		__m128 radius128 = _mm_set_ps(Radius, other.Radius, Radius, other.Radius);
		__m128 phiTrig128 = _mm_set_ps(sinPhi_this, sinPhi_other, sinPhi_this, sinPhi_other);
		__m128 thetaTrig128 = _mm_set_ps(cosTheta_this, cosTheta_other, sinTheta_this, sinTheta_other);
		__m128 mul128 = _mm_mul_ps(radius128, phiTrig128);
		mul128 = _mm_mul_ps(mul128, thetaTrig128);
		__m128 phiTrigCont128 = _mm_set_ps(cosPhi_this, cosPhi_other, 0.0f, 0.0f);
		__m128 mulCont128 = _mm_mul_ps(radius128, phiTrigCont128);
		__m128 addA128 = _mm_shuffle_ps(mulCont128, mul128, _MM_SHUFFLE(3, 1, 3, 0));
		__m128 addB128 = _mm_shuffle_ps(mulCont128, mul128, _MM_SHUFFLE(2, 0, 2, 0));
		__m128 cartesian128 = _mm_add_ps(addA128, addB128);
		float cartesianResults[4];
		_mm_store_ps(cartesianResults, cartesian128);
		__m128 cartesianSquared128 = _mm_mul_ps(cartesian128, cartesian128);
		float cartesianSquaredResults[4];
		_mm_store_ps(cartesianSquaredResults, cartesianSquared128);

		float radius = Math::SquareRoot(cartesianSquaredResults[3] + cartesianSquaredResults[2] + cartesianSquaredResults[1]);
		float phi = Math::Arccos(cartesianResults[1] / radius);
		float theta = Math::Arctan2(cartesianResults[2], cartesianResults[3]);
		SphericalVector resultVec(radius, phi, theta);

		return resultVec;
	}

	SphericalVector SphericalVector::operator-(const SphericalVector& other) const
	{
		// Add this vector with the negative of the other vector
		SphericalVector negOther = other.operator-();
		SphericalVector resultVec = operator+(negOther);

		return resultVec;
	}

	SphericalVector SphericalVector::operator*(float scalar) const
	{
		// If the scalar is positive, scale up the radius
		if (scalar > 0)
		{
			SphericalVector resultVec(Radius * scalar, Phi, Theta);
			return resultVec;
		}
		// If the scalar is negative, scale up the radius, but keep the radius positive and instead flip phi over the horizontal axis and rotate theta around the vertical axis to get the correct direction
		else
		{
			SphericalVector resultVec(Radius * -scalar, Math::PI - Phi, Theta - Math::PI);
			return resultVec;
		}
	}

	SphericalVector SphericalVector::operator/(float scalar) const
	{
		// Multiply this vector with the inverse of the scalar
		float inverseScalar = 1.0f / scalar;
		SphericalVector resultVec = operator*(inverseScalar);

		return resultVec;
	}

	SphericalVector SphericalVector::operator-() const
	{
		// Flip phi over the horizontal rotate theta around the vertical
		SphericalVector resultVec(Radius, Math::PI - Phi, Theta - Math::PI);

		return resultVec;
	}

	SphericalVector operator*(float scalar, const SphericalVector& cv)
	{
		SphericalVector resultVec = cv.operator*(scalar);

		return resultVec;
	}

}
