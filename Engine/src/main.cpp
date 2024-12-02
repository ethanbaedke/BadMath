#include <iostream>
#include <string>

#include "Mathematics/CartesianVector.h"
#include "Mathematics/CylindricalVector.h"
#include "Mathematics/SphericalVector.h"
#include "Mathematics/Matrix.h"
#include "Mathematics/Quaternion.h"
#include "Mathematics/Random.h"

#include "Core/RenderManager.h"

using namespace Lumex::Mathematics;
using namespace Lumex::Core;

void DEBUG_Matrix44(const Matrix44& matrix)
{
	for (int row = 0; row < 4; row++)
	{
		const float* currentRow = matrix[row];
		std::cout << "	";
		for (int column = 0; column < 4; column++)
		{
			std::cout << currentRow[column] << " ";
		}
		std::cout << std::endl;
	}
}

void TEST_Matrix44(const Matrix44& matA, const Matrix44& matB)
{
	std::cout << std::endl << "Testing 4x4 Matrix..." << std::endl;

	std::cout << "Identity Matrix" << std::endl;
	DEBUG_Matrix44(Matrix44::Identity());

	std::cout << "Matrix A" << std::endl;
	DEBUG_Matrix44(matA);

	std::cout << "Matrix B" << std::endl;
	DEBUG_Matrix44(matB);

	std::cout << "Matrix A + B" << std::endl;
	DEBUG_Matrix44(matA + matB);

	std::cout << "Matrix A - B" << std::endl;
	DEBUG_Matrix44(matA - matB);

	std::cout << "Matrix A * B" << std::endl;
	DEBUG_Matrix44(matA * matB);

	std::cout << "Matrix A * 10" << std::endl;
	DEBUG_Matrix44(matA * 10.0f);

	std::cout << "Matrix A / 10" << std::endl;
	DEBUG_Matrix44(matA / 10.0f);

	std::cout << "Matrix Transpose of A" << std::endl;
	DEBUG_Matrix44(matA.Transpose());
}

void TEST_Matrices()
{
	float valuesA[4][4] = { {10.0f, 11.0f, 12.0f, 13.0f}, {14.0f, 15.0f, 16.0f, 17.0f}, {18.0f, 19.0f, 20.0f, 21.0f}, {22.0f, 23.0f, 24.0f, 25.0f} };
	float valuesB[4][4] = { {10.0f, 12.0f, 14.0f, 16.0f}, {18.0f, 20.0f, 22.0f, 24.0f}, {26.0f, 28.0f, 30.0f, 32.0f}, {34.0f, 36.0f, 38.0f, 40.0f} };
	Matrix44 matA(valuesA);
	Matrix44 matB(valuesB);
	TEST_Matrix44(matA, matB);
}

void DEBUG_SphericalVector(const SphericalVector& vector)
{
	std::cout << "	Radius = " + std::to_string(vector.Radius) << std::endl;
	std::cout << "	Phi = " + std::to_string(vector.Phi) << std::endl;
	std::cout << "	Theta = " + std::to_string(vector.Theta) << std::endl;
	std::cout << "	Magnitude = " << std::to_string(vector.Radius) << std::endl;
	std::cout << "	Squared Magnitude = " << std::to_string(vector.Radius * vector.Radius) << std::endl;
}

void DEBUG_CylindricalVector(const CylindricalVector& vector)
{
	std::cout << "	Height = " + std::to_string(vector.Height) << std::endl;
	std::cout << "	Radius = " + std::to_string(vector.Radius) << std::endl;
	std::cout << "	Theta = " + std::to_string(vector.Theta) << std::endl;
	std::cout << "	Magnitude = " << std::to_string(vector.Magnitude()) << std::endl;
	std::cout << "	Squared Magnitude = " << std::to_string(vector.SquaredMagnitude()) << std::endl;
}

void DEBUG_CartesianVector(const CartesianVector& vector)
{
	std::cout << "	X = " + std::to_string(vector.X) << std::endl;
	std::cout << "	Y = " + std::to_string(vector.Y) << std::endl;
	std::cout << "	Z = " + std::to_string(vector.Z) << std::endl;
	std::cout << "	Magnitude = " << std::to_string(vector.Magnitude()) << std::endl;
	std::cout << "	Squared Magnitude = " << std::to_string(vector.SquaredMagnitude()) << std::endl;
}

void TEST_CartesianVector(const CartesianVector& vecA, const CartesianVector& vecB)
{
	std::cout << std::endl << "Testing Cartesian Vector..." << std::endl;

	std::cout << "Vector A" << std::endl;
	DEBUG_CartesianVector(vecA);

	std::cout << "Vector B" << std::endl;
	DEBUG_CartesianVector(vecB);

	std::cout << "Vector A + B" << std::endl;
	DEBUG_CartesianVector(vecA + vecB);

	std::cout << "Vector -A" << std::endl;
	DEBUG_CartesianVector(-vecA);

	std::cout << "Vector A - B" << std::endl;
	DEBUG_CartesianVector(vecA - vecB);

	std::cout << "Vector A * 10" << std::endl;
	DEBUG_CartesianVector(vecA * 10.0f);

	std::cout << "Vector A / 10" << std::endl;
	DEBUG_CartesianVector(vecA / 10.0f);

	std::cout << "A Dot B = " << std::to_string(vecA.DotProduct(vecB)) << std::endl;

	std::cout << "Vector A Cross B" << std::endl;
	DEBUG_CartesianVector(vecA.CrossProduct(vecB));

	std::cout << "Vector Linear Interpolate A->B (50%)" << std::endl;
	DEBUG_CartesianVector(vecA.LinearInterpolate(vecB, 0.5f));

	std::cout << "Vector Normalized A" << std::endl;
	DEBUG_CartesianVector(vecA.Normalized());
}

void TEST_CylindricalVector(const CylindricalVector& vecA, const CylindricalVector& vecB)
{
	std::cout << std::endl << "Testing Cylindrical Vector..." << std::endl;

	std::cout << "Vector A" << std::endl;
	DEBUG_CylindricalVector(vecA);

	std::cout << "Vector B" << std::endl;
	DEBUG_CylindricalVector(vecB);

	std::cout << "Vector A + B" << std::endl;
	DEBUG_CylindricalVector(vecA + vecB);

	std::cout << "Vector -A" << std::endl;
	DEBUG_CylindricalVector(-vecA);

	std::cout << "Vector A - B" << std::endl;
	DEBUG_CylindricalVector(vecA - vecB);

	std::cout << "Vector A * 10" << std::endl;
	DEBUG_CylindricalVector(vecA * 10.0f);

	std::cout << "Vector A / 10" << std::endl;
	DEBUG_CylindricalVector(vecA / 10.0f);

	std::cout << "A Dot B = " << vecA.DotProduct(vecB) << std::endl;

	std::cout << "Vector Linear Interpolate A->B (50%)" << std::endl;
	DEBUG_CylindricalVector(vecA.LinearInterpolate(vecB, 0.5f));

	std::cout << "Vector Normalized A" << std::endl;
	DEBUG_CylindricalVector(vecA.Normalized());

	std::cout << "Convert A to Cartesian Vector" << std::endl;
	DEBUG_CartesianVector(vecA.ToCartesian());

	std::cout << "Convert B to Cartesian Vector" << std::endl;
	DEBUG_CartesianVector(vecB.ToCartesian());
}

void TEST_SphericalVector(const SphericalVector& vecA, const SphericalVector& vecB)
{
	std::cout << std::endl << "Testing Spherical Vector..." << std::endl;

	std::cout << "Vector A" << std::endl;
	DEBUG_SphericalVector(vecA);

	std::cout << "Vector B" << std::endl;
	DEBUG_SphericalVector(vecB);

	std::cout << "Vector A + B" << std::endl;
	DEBUG_SphericalVector(vecA + vecB);

	std::cout << "Vector -A" << std::endl;
	DEBUG_SphericalVector(-vecA);

	std::cout << "Vector A - B" << std::endl;
	DEBUG_SphericalVector(vecA - vecB);

	std::cout << "Vector A * 10" << std::endl;
	DEBUG_SphericalVector(vecA * 10.0f);

	std::cout << "Vector A / 10" << std::endl;
	DEBUG_SphericalVector(vecA / 10.0f);

	std::cout << "A Dot B = " << vecA.DotProduct(vecB) << std::endl;

	std::cout << "Vector Linear Interpolate A->B (50%)" << std::endl;
	DEBUG_SphericalVector(vecA.LinearInterpolate(vecB, 0.5f));

	std::cout << "Vector Normalized A" << std::endl;
	DEBUG_SphericalVector(vecA.Normalized());

	std::cout << "Convert A to Cartesian Vector" << std::endl;
	DEBUG_CartesianVector(vecA.ToCartesian());

	std::cout << "Convert B to Cartesian Vector" << std::endl;
	DEBUG_CartesianVector(vecB.ToCartesian());
}

void TEST_Vectors()
{
	std::cout << std::endl << "Testing Vector Classes..." << std::endl;

	CartesianVector cartesianVecA(1.0f, 2.0f, 3.0f);
	CartesianVector cartesianVecB(2.0f, 4.0f, 6.0f);
	TEST_CartesianVector(cartesianVecA, cartesianVecB);

	CylindricalVector cylindricalVecA(2.0f, Math::SquareRoot(10.0f), Math::Arctan2(3.0f, 1.0f));
	CylindricalVector cylindricalVecB(4.0f, Math::SquareRoot(40.0f), Math::Arctan2(6.0f, 2.0f));
	TEST_CylindricalVector(cylindricalVecA, cylindricalVecB);

	SphericalVector sphericalVecA(Math::SquareRoot(14.0f), Math::Arccos(2.0f / Math::SquareRoot(14.0f)), Math::Arctan2(3.0f, 1.0f));
	SphericalVector sphericalVecB(Math::SquareRoot(56.0f), Math::Arccos(4.0f / Math::SquareRoot(56.0f)), Math::Arctan2(6.0f, 2.0f));
	TEST_SphericalVector(sphericalVecA, sphericalVecB);
}

void TEST_UnitCircle()
{
	std::cout << std::endl << "Testing Unit Cirlce Calculations..." << std::endl;

	std::cout << "Sine Approximation (-5/3 PI) = " + std::to_string(Math::Sin((-5.0f / 3.0f) * Math::PI)) << std::endl;
	std::cout << "Sine Approximation (4/3 PI) = " + std::to_string(Math::Sin((4.0f / 3.0f) * Math::PI)) << std::endl;

	std::cout << "Cosine Approximation (-5/3 PI) = " + std::to_string(Math::Cos((-5.0f / 3.0f) * Math::PI)) << std::endl;
	std::cout << "Cosine Approximation (4/3 PI) = " + std::to_string(Math::Cos((4.0f / 3.0f) * Math::PI)) << std::endl;

	std::cout << "Tangent Approximation (-5/3 PI) = " + std::to_string(Math::Tan((-5.0f / 3.0f) * Math::PI)) << std::endl;
	std::cout << "Tangent Approximation (4/3 PI) = " + std::to_string(Math::Tan((4.0f / 3.0f) * Math::PI)) << std::endl;

	std::cout << "Arccos Approximation (y=1, x=-1) = " + std::to_string(Math::Arccos(1.0f / -1.0f)) << std::endl;
	std::cout << "Arccos Approximation (y=-1, x=-1) = " + std::to_string(Math::Arccos(-1.0f / -1.0f)) << std::endl;

	std::cout << "Arctan2 Approximation (y=1, x=-1) = " + std::to_string(Math::Arctan2(1.0f, -1.0f)) << std::endl;
	std::cout << "Arctan2 Approximation (y=-1, x=-1) = " + std::to_string(Math::Arctan2(-1.0f, -1.0f)) << std::endl;
}

void DEBUG_Quaternion(const Quaternion& quaternion)
{
	CartesianVector Qv = quaternion.GetQv();
	std::cout << "	Qx = " + std::to_string(Qv.X) << std::endl;
	std::cout << "	Qy = " + std::to_string(Qv.Y) << std::endl;
	std::cout << "	Qz = " + std::to_string(Qv.Z) << std::endl;
	std::cout << "	Qw = " << std::to_string(quaternion.GetQw()) << std::endl;
}

void TEST_Quaternion(const Quaternion& quat, const CartesianVector& vec)
{
	std::cout << std::endl << "Testing Quaternion..." << std::endl;

	std::cout << "Quaternion" << std::endl;
	DEBUG_Quaternion(quat);

	std::cout << "Vector" << std::endl;
	DEBUG_CartesianVector(vec);

	std::cout << "Vector rotated by Quaternion" << std::endl;
	DEBUG_CartesianVector(quat.ApplyToCartesianVector(vec));
}

void TEST_Random()
{
	std::cout << std::endl << "Testing Random..." << std::endl;
	std::cout << "Random Integer: " + std::to_string(Random::GetInt(-1, 1)) << std::endl;
	std::cout << "Random Integer: " + std::to_string(Random::GetInt(-1, 1)) << std::endl;
	std::cout << "Random Integer: " + std::to_string(Random::GetInt(-1, 1)) << std::endl;
	std::cout << "Random Integer: " + std::to_string(Random::GetInt(-1, 1)) << std::endl;
	std::cout << "Random Integer: " + std::to_string(Random::GetInt(-1, 1)) << std::endl;
	std::cout << "Random Float: " + std::to_string(Random::GetFloat(-1.0f, 1.0f)) << std::endl;
	std::cout << "Random Float: " + std::to_string(Random::GetFloat(-1.0f, 1.0f)) << std::endl;
	std::cout << "Random Float: " + std::to_string(Random::GetFloat(-1.0f, 1.0f)) << std::endl;
	std::cout << "Random Float: " + std::to_string(Random::GetFloat(-1.0f, 1.0f)) << std::endl;
	std::cout << "Random Float: " + std::to_string(Random::GetFloat(-1.0f, 1.0f)) << std::endl;
}

void TEST_Mathematics()
{
	std::cout << std::endl << "Testing Basic Mathematics..." << std::endl;
	std::cout << "Square Root Approximation (64) = " + std::to_string(Math::SquareRoot(64.0f)) << std::endl;
	std::cout << "Square Root Approximation (10,000,000,000) = " + std::to_string(Math::SquareRoot(10000000000.0f)) << std::endl;

	std::cout << "Linear Interpolation (-3, 1) (50%) = " + std::to_string(Math::LinearInterpolate(-3.0f, 1.0f, 0.5f)) << std::endl;
	std::cout << "Linear Interpolation (-1, 1) (75%) = " + std::to_string(Math::LinearInterpolate(-1.0f, 1.0f, 0.75f)) << std::endl;

	TEST_UnitCircle();
	TEST_Vectors();
	TEST_Matrices();

	// This quaternion is a 180 degree rotation around the +x-axis
	Quaternion quat(CartesianVector(1.0f, 0.0f, 0.0f), Math::PI);
	CartesianVector vec(0.0f, 1.0f, 0.0f);
	TEST_Quaternion(quat, vec);

	TEST_Random();
}

int main()
{
	TEST_Mathematics();
	std::cout << std::endl;

	// Test making a singleton
	RenderManager* renderManager = new RenderManager();
	std::cout << std::to_string(RenderManager::Get().TestFunction()) << std::endl;

	return 0;
}