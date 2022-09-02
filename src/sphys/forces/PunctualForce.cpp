#include "sphys/RigidBody.h"
#include "sphys/forces/PunctualForce.h"

namespace sphys {

	PunctualForce::PunctualForce(const glm::vec3& value, const glm::vec3& point) :
		mValue(value), mPoint(point) {}


	Force::ForceTorquePair PunctualForce::calculate(const RigidBody& rigidBody) const
	{
		glm::vec3 force = mValue;
		glm::vec3 torque = glm::cross(mPoint - rigidBody.getState().position, mValue);
		return { force, torque };
	}

}
