#ifndef CONSTRAINTS_SYSTEM_H
#define CONSTRAINTS_SYSTEM_H

#include <map>
#include "../physics/constraints/NormalConstraint.h"
#include "../physics/constraints/FrictionConstraint.h"
#include "../collision/Manifold.h"
#include "../utils/FixedVector.h"
#include "ISystem.h"

namespace se::app {

	class Application;
	class CollisionEvent;


	/**
	 * Class ConstraintsSystem, it's a System used for updating the Entities'
	 * physics data with the constraints changes
	 */
	class ConstraintsSystem : public ISystem
	{
	private:	// Nested types
		/** Holds all the Constraints per Contact */
		struct ContactConstraints
		{
			physics::NormalConstraint normalConstraint;
			physics::FrictionConstraint frictionConstraints[2];
		};

		using ManifoldConstraints = utils::FixedVector<
			ContactConstraints, collision::Manifold::kMaxContacts
		>;

	private:	// Attributes
		/** The velocity of the constraint resolution process of the
		 * NormalConstraints */
		static constexpr float kCollisionBeta = 0.1f;

		/** The restitution factor of all the NormalConstraints */
		static constexpr float kCollisionRestitutionFactor = 0.2f;

		/** The slop penetration value of all the NormalConstraints */
		static constexpr float kCollisionSlopPenetration = 0.005f;

		/** The slop restitution value of all the NormalConstraints */
		static constexpr float kCollisionSlopRestitution = 0.5f;

		/** The gravity acceleration value of all the FrictionConstraints */
		static constexpr float kFrictionGravityAcceleration = 9.8f;

		/** The Application that holds the PhysicsEngine and the EventManager
		 * used for updating Entities' RigidBodies and being notified of the
		 * Collisions */
		Application& mApplication;

		/** The NormalConstraints generated as a consecuence of the
		 * PhysicsEntities collisions */
		std::map<const collision::Manifold*, ManifoldConstraints>
			mManifoldConstraintsMap;

	public:		// Functions
		/** Creates a new ConstraintsSystem
		 *
		 * @param	application a reference to the Application that holds the
		 *			current System */
		ConstraintsSystem(Application& application);

		/** Class destructor */
		~ConstraintsSystem();

		/** Notifies the ConstraintsSystem of the given event
		 *
		 * @param	event the IEvent to notify */
		virtual void notify(const IEvent& event) override;

		/** Function that the EntityDatabase will call when an Entity is
		 * added
		 *
		 * @param	entity the new Entity */
		virtual void onNewEntity(Entity entity);

		/** Function that the EntityDatabase will call when an Entity is
		 * removed
		 *
		 * @param	entity the Entity to remove */
		virtual void onRemoveEntity(Entity entity);

		/** Solves the Constraints between the RigidBodies of the entities
		 *
		 * @param	delta the elapsed time since the last update in seconds */
		virtual void update() override;
	private:
		/** Handles the given CollisionEvent by creating ContactConstraints
		 * between the colliding Entities
		 *
		 * @param	event the CollisionEvent to handle */
		void onCollisionEvent(const CollisionEvent& event);

		/** Adds contact constraints to the ConstraintsSystem for resolving the
		 * collision detected in the given contact Manifold
		 *
		 * @param	rb1 a pointer to the first RigidBody of the Constraints
		 * @param	rb1 a pointer to the second RigidBody of the Constraints
		 * @param	manifold a pointer to the contact Manifold */
		void handleIntersectingManifold(
			physics::RigidBody* rb1, physics::RigidBody* rb2,
			const collision::Manifold* manifold
		);

		/** Removes all the Manifold contact constraints from the ConstraintsSystem
		 *
		 * @param	manifold a pointer to the contact Manifold */
		void handleDisjointManifold(const collision::Manifold* manifold);
	};

}

#endif	// CONSTRAINTS_SYSTEM_H