#include "Quaternion.h"

#include "xmmintrin.h"

namespace Lumex {
	namespace Mathematics {

		Quaternion::Quaternion()
		{
		}

		Quaternion::Quaternion(const CartesianVector& vector, float theta)
		{
			CartesianVector normVec = vector.Normalized();
			m_Qv = normVec * Math::Sin(theta / 2.0f);
			m_Qw = Math::Cos(theta / 2.0f);
		}

		CartesianVector Quaternion::ApplyToCartesianVector(const CartesianVector& vector) const
		{
			// Get the inverse of this quaternion
			Quaternion inverse(*this);
			inverse.m_Qv = -(inverse.m_Qv);

			// Put the vector in quaternion form
			Quaternion vecQuat;
			vecQuat.m_Qv = vector;

			Quaternion resultQuat = (this->operator*(vecQuat)).operator*(inverse);

			// Put the vector back into vector form
			CartesianVector resultVec(resultQuat.m_Qv);

			return resultVec;
		}

		Quaternion Quaternion::operator*(const Quaternion& other) const
		{
			Quaternion resultQuat;
			resultQuat.m_Qv = (other.m_Qv * m_Qw) + (m_Qv * other.m_Qw) + (m_Qv.CrossProduct(other.m_Qv));
			resultQuat.m_Qw = (m_Qw * other.m_Qw) + (m_Qv.DotProduct(other.m_Qv));

			return resultQuat;
		}
	}
}