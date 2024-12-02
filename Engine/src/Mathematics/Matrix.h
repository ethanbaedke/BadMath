#pragma once

namespace Lumex {
	namespace Mathematics {

		/* A 4x4 Matrix, this can be indexed like a container with [Row][Column] */
		class Matrix44
		{
		public:
			/* Returns the identity matrix */
			static Matrix44 Identity();

			/* Constructors */
			Matrix44();
			Matrix44(float values[4][4]);

			/* Returns the transpose of this matrix */
			Matrix44 Transpose() const;

			/* Operator overloads */
			float* operator[](int row); // Returns a pointer to the first float of the input row
			const float* operator[](int row) const; // This is the readonly version of the above function
			Matrix44 operator+(const Matrix44& other) const;
			Matrix44 operator-(const Matrix44& other) const;
			Matrix44 operator*(const Matrix44& other) const;
			Matrix44 operator*(float scalar) const;
			Matrix44 operator/(float scalar) const;

		private:
			/* Values are indexed [Row][Column] */
			alignas(16) float m_Values[4][4] = {};
		};
	}
}