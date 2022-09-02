#include "sphys/RigidBody.h"
#include "sphys/forces/Gravity.h"

namespace sphys {

	Gravity::Gravity(const float& gravity) : mGravity(gravity) {}


	Force::ForceTorquePair Gravity::calculate(const RigidBody& rigidBody) const
	{
		glm::vec3 force(0.0f), torque(0.0f);

		float invertedMass = rigidBody.getProperties().invertedMass;
		if (invertedMass > 0.0f) {
			force = glm::vec3(0.0f, mGravity / invertedMass, 0.0f);
		}

		return { force, torque };
	}

}
