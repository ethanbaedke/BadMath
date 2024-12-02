#include "Matrix.h"

#include <xmmintrin.h>

namespace Lumex {
	namespace Mathematics {

		Matrix44 Matrix44::Identity()
		{
			Matrix44 identityMat;
			for (int i = 0; i < 4; i++)
			{
				identityMat[i][i] = 1.0f;
			}
			return identityMat;
		}

		Matrix44::Matrix44()
		{
		}

		Matrix44::Matrix44(float values[4][4])
		{
			// Copy the input values into this matrix
			for (int i = 0; i < 4; i++)
			{
				__m128 row128 = _mm_loadu_ps(values[i]);
				_mm_store_ps(m_Values[i], row128);
			}
		}

		Matrix44 Matrix44::Transpose() const
		{
			// Fill the rows of the new matrix with the columns of this matrix
			Matrix44 resultMat;
			for (int i = 0; i < 4; i++)
			{
				__m128 column128 = _mm_set_ps(m_Values[3][i], m_Values[2][i], m_Values[1][i], m_Values[0][i]);
				_mm_store_ps(resultMat[i], column128);
			}

			return resultMat;
		}

		float* Matrix44::operator[](int row)
		{
			return m_Values[row];
		}

		const float* Matrix44::operator[](int row) const
		{
			return m_Values[row];
		}

		Matrix44 Matrix44::operator+(const Matrix44& other) const
		{
			Matrix44 resultMat;
			for (int i = 0; i < 4; i++)
			{
				// Load the rows of both matrices, add them, and store the value in the new matrix
				__m128 rowThis128 = _mm_load_ps(m_Values[i]);
				__m128 rowOther128 = _mm_load_ps(other.m_Values[i]);
				__m128 result128 = _mm_add_ps(rowThis128, rowOther128);
				_mm_store_ps(resultMat[i], result128);
			}

			return resultMat;
		}

		Matrix44 Matrix44::operator-(const Matrix44& other) const
		{
			Matrix44 resultMat;
			for (int i = 0; i < 4; i++)
			{
				// Load the rows of both matrices, subtract the other from this, and store the value in the new matrix
				__m128 rowThis128 = _mm_load_ps(m_Values[i]);
				__m128 rowOther128 = _mm_load_ps(other.m_Values[i]);
				__m128 result128 = _mm_sub_ps(rowThis128, rowOther128);
				_mm_store_ps(resultMat[i], result128);
			}

			return resultMat;
		}

		Matrix44 Matrix44::operator*(const Matrix44& other) const
		{
			// Load rows of this matrix and the columns of the other matrix
			__m128 rows[4];
			__m128 columns[4];
			for (int i = 0; i < 4; i++)
			{
				rows[i] = _mm_load_ps(m_Values[i]);
				columns[i] = _mm_set_ps(other[3][i], other[2][i], other[1][i], other[0][i]);
			}

			// For each row, multiply it by each column and add the values together, then put the newly calculated row into the new matrix
			Matrix44 resultMat;
			for (int i = 0; i < 4; i++)
			{
				// Handle row/column multiplication
				__m128 mul1_128 = _mm_mul_ps(rows[i], columns[0]);
				__m128 mul2_128 = _mm_mul_ps(rows[i], columns[1]);
				__m128 mul3_128 = _mm_mul_ps(rows[i], columns[2]);
				__m128 mul4_128 = _mm_mul_ps(rows[i], columns[3]);

				// Swap the first half of mul2 with the second half of mul1, then add our new registers
				__m128 swapA_128 = _mm_shuffle_ps(mul1_128, mul2_128, _MM_SHUFFLE(1, 0, 1, 0));
				__m128 swapB_128 = _mm_shuffle_ps(mul1_128, mul2_128, _MM_SHUFFLE(3, 2, 3, 2));
				__m128 result1_128 = _mm_add_ps(swapA_128, swapB_128);

				// Repeat for mul3 and mul4
				swapA_128 = _mm_shuffle_ps(mul3_128, mul4_128, _MM_SHUFFLE(1, 0, 1, 0));
				swapB_128 = _mm_shuffle_ps(mul3_128, mul4_128, _MM_SHUFFLE(3, 2, 3, 2));
				__m128 result2_128 = _mm_add_ps(swapA_128, swapB_128);

				// Line up our results by swapping values similar to how we did above, and add them
				// This gives us the final values for our current row
				swapA_128 = _mm_shuffle_ps(result1_128, result2_128, _MM_SHUFFLE(2, 0, 2, 0));
				swapB_128 = _mm_shuffle_ps(result1_128, result2_128, _MM_SHUFFLE(3, 1, 3, 1));
				__m128 result3_128 = _mm_add_ps(swapA_128, swapB_128);

				// Move our results directly into our new matrix
				_mm_store_ps(resultMat[i], result3_128);
			}

			return resultMat;
		}

		Matrix44 Matrix44::operator*(float scalar) const
		{
			__m128 scalar128 = _mm_set1_ps(scalar);

			Matrix44 resultMat;
			for (int i = 0; i < 4; i++)
			{
				// Load a row of this matrix and multiply it with our scalar, then put the value in the new matrix
				__m128 row128 = _mm_load_ps(m_Values[i]);
				__m128 result128 = _mm_mul_ps(row128, scalar128);
				_mm_store_ps(resultMat[i], result128);
			}

			return resultMat;
		}

		Matrix44 Matrix44::operator/(float scalar) const
		{
			Matrix44 resultMat = operator*(1.0f / scalar);

			return resultMat;
		}
	}
}