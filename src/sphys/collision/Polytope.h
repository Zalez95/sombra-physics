#ifndef SPHYS_POLYTOPE_H
#define SPHYS_POLYTOPE_H

#include <stdext/ArrayVector.h>
#include "sphys/collision/SupportPoint.h"
#include "sphys/collision/HalfEdgeMesh.h"

namespace sphys {

	class ConvexCollider;


	/**
	 * Struct FaceDistanceData, it stores the distance data of a face to
	 * the origin
	 */
	struct FaceDistanceData
	{
		/** The 3D coordinates of the closest point in the face to the
		 * origin */
		glm::vec3 closestPoint;

		/** The distance of the closest Point to the origin */
		float distance;

		/** If the calculated closest point is inside the face or not */
		bool inside;

		/** The barycentric coordinates of the closest point in the face to
		 * the origin */
		glm::vec3 closestPointBarycentricCoords;
	};


	/**
	 * Class Polytope, it's the class that holds the polytope data that the EPA
	 * algorithm must expand.
	 * This class also handles the Polytope creation from the simplex generated
	 * by the GJK algorithm, which also serves as input to the EPA algorithm.
	 */
	class Polytope
	{
	private:	// Attributes
		static constexpr float sKEpsilon = 0.0001f;

		/** The precision of the calculated projections */
		float mPrecision;

		/** The Half-Edge Mesh with the convex hull of the current Mesh */
		HalfEdgeMesh mMesh;

		/** The normal vectors of each HEFace */
		stdext::ReleaseVector<glm::vec3> mFaceNormals;

		/** The distance data of eahc HEFace */
		stdext::ReleaseVector<FaceDistanceData> mFaceDistances;

		/** The SupportPoint of each HEVertex */
		stdext::ReleaseVector<SupportPoint> mVertexSupportPoints;

	public:		//Functions
		/** Creates a new Polytope from the given simplex points by expanding it
		 * until a tetrahedron is created
		 *
		 * @param	simplex the 4 initial simplex points
		 * @param	precision the precision of the projected points of the
		 *			polytope */
		Polytope(
			const stdext::ArrayVector<SupportPoint, 4>& simplex,
			float precision
		);

		/** @return	the HalfEdgeMesh of the Polytope */
		const HalfEdgeMesh& getMesh() const { return mMesh; };

		/** @return	the normal vectors of the HEFaces of the Polytope's
		 *			HalfEdgeMesh */
		const stdext::ReleaseVector<glm::vec3>& getNormals() const
		{ return mFaceNormals; };

		/** Returns the SupportPoint of the given Polytope HEVertex
		 *
		 * @param	iVertex the index of the HEVertex in the Polytope
		 * @return	the SupportPoint of the HEVertex */
		const SupportPoint& getSupportPoint(int iVertex) const
		{ return mVertexSupportPoints[iVertex]; };

		/** Returns the normal vector of the given Polytope HEFace
		 *
		 * @param	iFace the index of the HEFace in the Polytope
		 * @return	the normal vector of the HEFace */
		const glm::vec3& getNormal(int iFace) const
		{ return mFaceNormals[iFace]; };

		/** Returns the FaceDistanceData of the given Polytope HEFace
		 *
		 * @param	iFace the index of the HEFace in the Polytope
		 * @return	the FaceDistanceData of the HEFace */
		const FaceDistanceData& getDistanceData(int iFace) const
		{ return mFaceDistances[iFace]; };

		/** Creates a new HEVertex from the given SupportPoint and adds it to
		 * the Polytope Mesh
		 *
		 * @param	sp the SupportPoint used to create the HEVertex */
		int addVertex(const SupportPoint& sp);

		/** Creates a HEFace and pushes it at the front of the faces queue if
		 * it's closer to the origin than the current head, at the back
		 * otherwise
		 *
		 * @param	faceIndices the indices of the new face's vertices */
		int addFace(const stdext::ArrayVector<int, 3>& faceIndices);

		/** Removes the given HEFace and its data from the Polytope
		 *
		 * @param	iFace the index of the HEFace to remove */
		void removeFace(int iFace);
	};

}

#endif		// SPHYS_POLYTOPE_H
