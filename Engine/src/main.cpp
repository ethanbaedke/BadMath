#include <iostream>
#include <string>

#include "Mathematics/CartesianVector.h"
#include "Mathematics/CylindricalVector.h"
#include "Mathematics/SphericalVector.h"

using namespace Lumex;

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

	std::cout << "Convert A to Cartesian Vector" << std::endl;
	DEBUG_CartesianVector(vecA.ToCartesian());

	std::cout << "Convert B to Cartesian Vector" << std::endl;
	DEBUG_CartesianVector(vecB.ToCartesian());
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

	std::cout << "Convert A to Cartesian Vector" << std::endl;
	DEBUG_CartesianVector(vecA.ToCartesian());

	std::cout << "Convert B to Cartesian Vector" << std::endl;
	DEBUG_CartesianVector(vecB.ToCartesian());
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

void TEST_Mathematics()
{
	std::cout << std::endl << "Testing Basic Mathematics..." << std::endl;
	std::cout << "Square Root Approximation (64) = " + std::to_string(Math::SquareRoot(64.0f)) << std::endl;
	std::cout << "Square Root Approximation (10,000,000,000) = " + std::to_string(Math::SquareRoot(10000000000.0f)) << std::endl;

	TEST_UnitCircle();
	TEST_Vectors();
}

int main()
{
	TEST_Mathematics();

	return 0;
}