#include "sphys/RigidBody.h"
#include "sphys/forces/DirectionalForce.h"

namespace sphys {

	DirectionalForce::DirectionalForce(const glm::vec3& value) :
		mValue(value) {}


	Force::ForceTorquePair DirectionalForce::calculate(const RigidBody&) const
	{
		return { mValue, glm::vec3(0.0f) };
	}

}
