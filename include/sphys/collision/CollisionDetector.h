#ifndef SPHYS_COLLISION_DETECTOR_H
#define SPHYS_COLLISION_DETECTOR_H

#include <map>
#include <mutex>
#include <stdext/MathUtils.h>
#include <stdext/ReleaseVector.h>
#include "CoarseCollisionDetector.h"
#include "FineCollisionDetector.h"

namespace sphys {

	class RigidBodyWorld;


	/**
	 * Class CollisionListener, class used for being notified of the collisions
	 * detected by the CollisionDetector
	 */
	class ICollisionListener
	{
	public:		// Functions
		/** Class destructor */
		virtual ~ICollisionListener() = default;

		/** Function called per collision Manifold updated
		 *
		 * @param	manifold the Manifold updated */
		virtual void onCollision(const Manifold& manidold) = 0;
	};


	/**
	 * Class CollisionDetector, it's a class used for detecting collisions
	 * between Colliders. It will also calculate the Manifolds and its Contact
	 * data.
	 *
	 * The collision detection it splitted in two phases, one coarse collision
	 * detection where we're going to check which colliders could be
	 * intersecting by its AABB intersections, and one fine collision detection
	 * where we will calculate the Contact data of the collisions.
	 */
	class CollisionDetector
	{
	public:		// Nested types
		using RayCastCallback = std::function<void(Collider*, const RayHit&)>;
	private:
		using ColliderPair = std::pair<const Collider*, const Collider*>;
		using ManifoldUPtr = std::unique_ptr<Manifold>;
		using ManifoldCallback = std::function<void(const Manifold&)>;

	private:	// Attributes
		/** A reference to the RigidBodyWorld that holds the RigidBodies */
		RigidBodyWorld& mParentWorld;

		/** The CoarseCollisionDetector of the CollisionDetector. We will use
		 * it to check what Colliders are intersecting in the broad phase of
		 * the collision detection step */
		CoarseCollisionDetector mCoarseCollisionDetector;

		/** The FineCollisionDetector of the CollisionDetector. We will use
		 * it to generate all the contact data */
		FineCollisionDetector mFineCollisionDetector;

		/** The Colliders that are colliding in the coarse collision detection
		 * step */
		std::vector<ColliderPair> mCoarseCollidersColliding;

		/** All the Manifolds that the CollisionDetector can hold */
		stdext::ReleaseVector<Manifold> mManifolds;

		/** Maps a pair of Colliders with the index of the Manifold of their
		 * collision */
		std::unordered_map<ColliderPair, std::size_t, stdext::PairHash>
			mCollidersManifoldMap;

		/** The listeners added to the CollisionDetector */
		std::vector<ICollisionListener*> mListeners;

		/** The mutex used for protecting @see mCoarseCollisionDetector,
		 * @see mManifolds, @see mCollidersManifoldMap and @see mListeners */
		std::mutex mMutex;

	public:		// Functions
		/** Creates a new CollisionDetector
		 *
		 * @param	parentWorld the RigidBodyWorld that holds all the
		 *			RigidBodies to update */
		CollisionDetector(RigidBodyWorld& parentWorld);

		/** Calculates all the collisions that are currently happening between
		 * the RigidBodies */
		void update();

		/** Adds the given Collider to the CollisionDetection so it will check
		 * if it collides or intersects
		 *
		 * @param	collider a pointer to the Collider to add */
		void addCollider(Collider* collider);

		/** Removes all the references to the given Collider
		 *
		 * @param	collider a pointer to the Collider to remove
		 * @note	the removed Manifolds won't be notified */
		void removeCollider(Collider* collider);

		/** Adds the given ICollisionListener to the CollisionDetector so it
		 * will be updated of the collisions
		 *
		 * @param	listener a pointer to the new ICollisionListener */
		void addListener(ICollisionListener* listener);

		/** Removes the given ICollisionListener from the CollisionDetector so
		 * it won't longer be updated of the collisions
		 *
		 * @param	listener a pointer to the ICollisionListener to remove */
		void removeListener(ICollisionListener* listener);

		/** Calculates all the intersections with the given ray
		 *
		 * @param	ray the ray to test
		 * @param	callback the function that must be called for
		 *			of the Colliders intersecting with the ray */
		void rayCastAll(const Ray& ray, const RayCastCallback& callback);

		/** Calculates the first intersection with the given ray
		 *
		 * @param	ray the ray to test
		 * @return	a pair with a pointer to the intersected Collider, nullptr
		 *			if it didn't intersect anything, and a RayCast object with
		 *			the result of the RayCast */
		std::pair<Collider*, RayHit> rayCastFirst(const Ray& ray);
	private:
		/** Broad/Coarse collision detection step */
		void broadCollisionDetection();

		/** Narrow/Fine collision detection step */
		void narrowCollisionDetection();

		/** Executes the narrow/Fine collision detection step for a single
		 * Collider pair
		 *
		 * @param	pair the pair to detect its collisions
		 * @param	newManifolds a vector where the new Manifolds will be
		 *			inserted */
		void singleNarrowCollision(
			const ColliderPair& pair, std::vector<Manifold>& newManifolds
		);
	};

}

#endif		// SPHYS_COLLISION_DETECTOR_H
