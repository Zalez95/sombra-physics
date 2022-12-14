#include <limits>
#include "sphys/collision/HalfEdgeMeshExt.h"
#include "sphys/collision/ConvexPolyhedron.h"

namespace sphys {

	ConvexPolyhedron::ConvexPolyhedron(const HalfEdgeMesh& meshData) : mTransformsMatrix(1.0f)
	{
		setLocalMesh(meshData);
	}


	HalfEdgeMesh ConvexPolyhedron::getLocalMesh() const
	{
		HalfEdgeMesh ret = mMesh;
		ret.vertices = mLocalVertices;
		return ret;
	}


	void ConvexPolyhedron::setLocalMesh(const HalfEdgeMesh& meshData)
	{
		mMesh = meshData;
		mLocalVertices = meshData.vertices;
		setTransforms(mTransformsMatrix);
	}


	void ConvexPolyhedron::setTransforms(const glm::mat4& transforms)
	{
		mTransformsMatrix = transforms;

		mMesh.vertices = mLocalVertices;
		for (HEVertex& vertex : mMesh.vertices) {
			vertex.location = mTransformsMatrix * glm::vec4(vertex.location, 1.0);
		}

		mUpdated = true;
	}


	AABB ConvexPolyhedron::getAABB() const
	{
		return calculateAABB(mMesh);
	}


	void ConvexPolyhedron::getFurthestPointInDirection(
		const glm::vec3& direction,
		glm::vec3& pointWorld, glm::vec3& pointLocal
	) const
	{
		int iVertex = getFurthestVertexInDirection(mMesh, direction);

		pointWorld = mMesh.vertices[iVertex].location;
		pointLocal = mLocalVertices[iVertex].location;
	}

}
