#ifndef SPHYS_CONVEX_POLYHEDRON_H
#define SPHYS_CONVEX_POLYHEDRON_H

#include "HalfEdgeMesh.h"
#include "ConvexCollider.h"

namespace sphys {

	/**
	 * Class ConvexPolyhedron, it's a ConvexCollider whose vertices form a
	 * convex shape
	 */
	class ConvexPolyhedron : public ConvexCollider
	{
	protected:	// Attributes
		/** The Mesh in world coordinates */
		HalfEdgeMesh mMesh;

		/** The HEVertices of the ConvexPolyhedron's in local space */
		stdext::ReleaseVector<HEVertex> mLocalVertices;

		/** The transformation matrix of the ConvexPolyhedron */
		glm::mat4 mTransformsMatrix;

	public:		// Functions
		/** Creates a new ConvexPolyhedron located at the origin of coordinates
		 *
		 * @param	meshData the convex 3D HalfEdgeMesh used to create the
		 *			ConvexPolyhedron. Empty mesh by default
		 * @note	the Mesh must be convex */
		ConvexPolyhedron(const HalfEdgeMesh& meshData = HalfEdgeMesh());
		ConvexPolyhedron(const ConvexPolyhedron& other) = default;
		ConvexPolyhedron(ConvexPolyhedron&& other) = default;

		/** Class destructor */
		virtual ~ConvexPolyhedron() = default;

		/** Assignment operator */
		ConvexPolyhedron& operator=(const ConvexPolyhedron& other) = default;
		ConvexPolyhedron& operator=(ConvexPolyhedron&& other) = default;

		/** @return	the convex 3D HalfEdgeMesh of the ConvexPolyhedron in local
		 *			space */
		HalfEdgeMesh getLocalMesh() const;

		/** Sets the convex 3D HalfEdgeMesh of the ConvexPolyhedron
		 *
		 * @param	meshData the convex 3D HalfEdgeMesh in local space used by
		 *			the ConvexPolyhedron */
		void setLocalMesh(const HalfEdgeMesh& meshData);

		/** @copydoc Collider::clone() */
		virtual std::unique_ptr<Collider> clone() const override
		{ return std::make_unique<ConvexPolyhedron>(*this); };

		/** @copydoc Collider::setTransforms() */
		void setTransforms(const glm::mat4& transforms) override;

		/** @copydoc Collider::getTransforms() */
		glm::mat4 getTransforms() const override { return mTransformsMatrix; };

		/** @copydoc Collider::getAABB() */
		AABB getAABB() const override;

		/** @copydoc ConvexCollider::getFurthestPointInDirection() */
		void getFurthestPointInDirection(
			const glm::vec3& direction,
			glm::vec3& pointWorld, glm::vec3& pointLocal
		) const override;
	};

}

#endif		// SPHYS_CONVEX_POLYHEDRON_H
