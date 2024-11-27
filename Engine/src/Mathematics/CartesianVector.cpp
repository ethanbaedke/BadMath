#include "CartesianVector.h"

#include <xmmintrin.h>

namespace Lumex {

		CartesianVector::CartesianVector()
		{
		}

		CartesianVector::CartesianVector(float x, float y, float z)
			: X(x), Y(y), Z(z)
		{
		}

		float CartesianVector::Magnitude() const
		{
			float sm = SquaredMagnitude();
			float mag = Math::SquareRoot(sm);
			return mag;
		}

		float CartesianVector::SquaredMagnitude() const
		{
			// Take X, Y, and Z to the 2nd power
			__m128 values128 = _mm_set_ps(0.0f, Z, Y, X);
			__m128 result128 = _mm_mul_ps(values128, values128);
			float results[4];
			_mm_store_ps(results, result128);

			// Sum X, Y, and Z
			float sum = results[0] + results[1] + results[2];

			return sum;
		}

		CartesianVector CartesianVector::Normalized() const
		{
			// Divide this vector by its magnitude
			float magnitude = Magnitude();
			CartesianVector resultVec = operator*(1.0f / magnitude);

			return resultVec;
		}

		float CartesianVector::DotProduct(const CartesianVector& other) const
		{
			// Multiply the X, Y, and Z components of each vector
			__m128 this128 = _mm_set_ps(0.0f, Z, Y, X);
			__m128 other128 = _mm_set_ps(0.0f, other.Z, other.Y, other.X);
			__m128 result128 = _mm_mul_ps(this128, other128);
			float results[4];
			_mm_store_ps(results, result128);

			// Sum the multiplied values
			float resultFloat = results[0] + results[1] + results[2];

			return resultFloat;
		}

		CartesianVector CartesianVector::CrossProduct(const CartesianVector& other) const
		{
			// (Ax, Ay, Az)
			__m128 this128 = _mm_set_ps(0.0f, Z, Y, X);

			// (By, Bz, Bx)
			__m128 other128 = _mm_set_ps(0.0f, other.X, other.Z, other.Y);

			// (Ax*By, Ay*Bz, Az*Bx)
			__m128 pos128 = _mm_mul_ps(this128, other128);

			// (Bz, Bx, By)
			other128 = _mm_shuffle_ps(other128, other128, _MM_SHUFFLE(3, 0, 2, 1));

			// (Ax*Bz, Ay*Bx, Az*By)
			__m128 sub128 = _mm_mul_ps(this128, other128);

			// (Ay*Bx, Az*By, Ax*Bz)
			sub128 = _mm_shuffle_ps(sub128, sub128, _MM_SHUFFLE(3, 0, 2, 1));

			// (Ax*By - Ay*Bx, Ay*Bz - Az*By, Az*Bx - Ax*Bz)
			__m128 result128 = _mm_sub_ps(pos128, sub128);

			// (Ay*Bz - Az*By, Az*Bx - Ax*Bz, Ax*By - Ay*Bx)
			result128 = _mm_shuffle_ps(result128, result128, _MM_SHUFFLE(3, 0, 2, 1));
			float results[4];
			_mm_store_ps(results, result128);

			// Create a new vector with the result components
			CartesianVector resultVec(results[0], results[1], results[2]);

			return resultVec;
		}

		CartesianVector CartesianVector::LinearInterpolate(const CartesianVector& other, float percent) const
		{
			// Treat both vectors like components of the new vector, with lengths based on the input percent
			CartesianVector thisComponent = operator*(1.0f - percent);
			CartesianVector otherComponent = other.operator*(percent);

			// Add these to get the resultent
			CartesianVector resultVec = thisComponent.operator+(otherComponent);
			
			return resultVec;
		}

		CartesianVector CartesianVector::operator+(const CartesianVector& other) const
		{
			// Sum the X, Y, and Z components of each vector
			__m128 this128 = _mm_set_ps(0.0f, Z, Y, X);
			__m128 other128 = _mm_set_ps(0.0f, other.Z, other.Y, other.X);
			__m128 result128 = _mm_add_ps(this128, other128);
			float results[4];
			_mm_store_ps(results, result128);

			// Create a new vector with the summed components
			CartesianVector resultVec(results[0], results[1], results[2]);

			return resultVec;
		}

		CartesianVector CartesianVector::operator-(const CartesianVector& other) const
		{
			// Add this vector with the negative of the other vector
			CartesianVector negOther = other.operator-();
			CartesianVector resultVec = operator+(negOther);

			return resultVec;
		}

		CartesianVector CartesianVector::operator*(float scalar) const
		{
			// Multiply the X, Y, and Z components of the vector by the scalar
			__m128 this128 = _mm_set_ps(0.0f, Z, Y, X);
			__m128 scalar128 = _mm_set1_ps(scalar);
			__m128 result128 = _mm_mul_ps(this128, scalar128);
			float results[4];
			_mm_store_ps(results, result128);

			// Create a new vector with the summed components
			CartesianVector resultVec(results[0], results[1], results[2]);

			return resultVec;
		}

		CartesianVector CartesianVector::operator/(float scalar) const
		{
			// Multiply this vector with the inverse of the scalar
			float inverseScalar = 1.0f / scalar;
			CartesianVector resultVec = operator*(inverseScalar);

			return resultVec;
		}

		CartesianVector CartesianVector::operator-() const
		{
			// Flip the sign bit on the X, Y, and Z components
			__m128 this128 = _mm_set_ps(0.0f, Z, Y, X);
			__m128 signMask128 = _mm_set1_ps(-0.0f);
			__m128 result128 = _mm_xor_ps(this128, signMask128);
			float results[4];
			_mm_store_ps(results, result128);

			// Create a new vector with the flipped components
			CartesianVector resultVec(results[0], results[1], results[2]);

			return resultVec;
		}

		CartesianVector operator*(float scalar, const CartesianVector& cv)
		{
			CartesianVector resultVec = cv.operator*(scalar);

			return resultVec;
		}
}