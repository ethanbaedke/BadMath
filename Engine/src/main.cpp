#include <iostream>
#include <string>

#include "Mathematics/CartesianVector.h"

using namespace Lumex::Mathematics;

void DEBUG_CartesianVector(const CartesianVector& cv)
{
	std::cout << "	X = " + std::to_string(cv.X) << std::endl;
	std::cout << "	Y = " + std::to_string(cv.Y) << std::endl;
	std::cout << "	Z = " + std::to_string(cv.Z) << std::endl;
	std::cout << "	Magnitude = " << std::to_string(cv.Magnitude()) << std::endl;
	std::cout << "	Squared Magnitude = " << std::to_string(cv.SquaredMagnitude()) << std::endl;
}

void TEST_CartesianVector(const CartesianVector& cvA, const CartesianVector& cvB)
{
	std::cout << std::endl << "Testing Cartesian Vector..." << std::endl;

	std::cout << "Vector A" << std::endl;
	DEBUG_CartesianVector(cvA);

	std::cout << "Vector B" << std::endl;
	DEBUG_CartesianVector(cvB);

	std::cout << "Vector A + B" << std::endl;
	DEBUG_CartesianVector(cvA + cvB);

	std::cout << "Vector -A" << std::endl;
	DEBUG_CartesianVector(-cvA);

	std::cout << "Vector A - B" << std::endl;
	DEBUG_CartesianVector(cvA - cvB);

	std::cout << "Vector A * 10" << std::endl;
	DEBUG_CartesianVector(cvA * 10.0f);

	std::cout << "Vector A / 10" << std::endl;
	DEBUG_CartesianVector(cvA / 10.0f);

	std::cout << "A Dot B = " << cvA.DotProduct(cvB) << std::endl;

	std::cout << "Vector A Cross B" << std::endl;
	DEBUG_CartesianVector(cvA.CrossProduct(cvB));

	std::cout << "Vector Linear Interpolate A->B (50%)" << std::endl;
	DEBUG_CartesianVector(cvA.LinearInterpolate(cvB, 0.5f));
}

void TEST_Vector()
{
	std::cout << std::endl << "Testing Vector Classes..." << std::endl;

	CartesianVector cvA(1.0f, 2.0f, 3.0f);
	CartesianVector cvB(2.0f, 4.0f, 6.0f);
	TEST_CartesianVector(cvA, cvB);
}

void TEST_Mathematics()
{
	std::cout << std::endl;
	std::cout << "Square Root Approximation (10,000,000,000) = " + std::to_string(SquareRoot(10000000000.0f)) << std::endl;
}

int main()
{
	TEST_Mathematics();
	TEST_Vector();

	return 0;
}