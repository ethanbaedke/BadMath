#pragma once

namespace Lumex {

	class Math
	{
	public:
		static const float PI;

		static float SquareRoot(float x);

		static float Sin(float radian);
		static float Cos(float radian);
		static float Tan(float radian);

		/* Returns the angle from the +x-axis to the point defined by x and y in Cartesian Coordinates */
		static float Arctan2(float x, float y);

	private:

		/* This is an approximation of the inverse of a square root that is often within 0.000002% of the true length */
		static float InverseSquareRoot(float x);

		/*
		* Normalizes a radian to a value that is between -PI/2 and PI/2
		* outFlipSign will be set to true if the results of the sine and cosine functions being called on the radian would give inverted results after normalizing the radian
		*/
		static float NormalizeRadian(float radian, bool* outFlipSign);

		/* These are approximations that are often within 0.000003% of the true value, assuming the input radian is normalized (see NormalizeRadian) */
		static float CalculateSinFromNormalizedRadian(float radian);
		static float CalculateCosFromNormalizedRadian(float radian);

		// This is an approximation of the arctangent of the input ratio (y/x) that is often within 0.02% of the true radian
		static float Arctan(float ratio);
	};

}