#include "se/graphics/3D/RenderableTerrain.h"
#include "se/graphics/core/GraphicsOperations.h"

namespace se::graphics {

	RenderableTerrain::RenderableTerrain(float size, float maxHeight, const std::vector<float>& lodDistances) :
		mQuadTree(size, lodDistances), mMaxHeight(maxHeight)
	{
		mMinimum = { -size, -mMaxHeight, -size };
		mMaximum = { size, mMaxHeight, size };
	}


	RenderableTerrain::RenderableTerrain(const RenderableTerrain& other) :
		Renderable3D(other),
		mQuadTree(other.mQuadTree), mMaxHeight(other.mMaxHeight) {}


	RenderableTerrain& RenderableTerrain::operator=(const RenderableTerrain& other)
	{
		Renderable3D::operator=(other);
		mQuadTree = other.mQuadTree;
		mMaxHeight = other.mMaxHeight;

		return *this;
	}


	Renderable3D& RenderableTerrain::setModelMatrix(const glm::mat4& modelMatrix)
	{
		Renderable3D::setModelMatrix(modelMatrix);

		float size = mQuadTree.getSize();
		std::array<glm::vec3, 8> localAABBVertices = {
			glm::vec3(-size,-mMaxHeight,-size),
			glm::vec3(-size,-mMaxHeight, size),
			glm::vec3(-size, mMaxHeight,-size),
			glm::vec3(-size, mMaxHeight, size),
			glm::vec3( size,-mMaxHeight,-size),
			glm::vec3( size,-mMaxHeight, size),
			glm::vec3( size, mMaxHeight,-size),
			glm::vec3( size, mMaxHeight, size)
		};

		mMinimum = mMaximum = mModelMatrix * glm::vec4(localAABBVertices[0], 1.0f);
		for (std::size_t i = 1; i < 8; ++i) {
			glm::vec3 vw = mModelMatrix * glm::vec4(localAABBVertices[i], 1.0f);
			mMinimum = glm::min(mMinimum, vw);
			mMaximum = glm::max(mMaximum, vw);
		}

		return *this;
	}


	void RenderableTerrain::setHighestLodLocation(const glm::vec3& location)
	{
		mQuadTree.updateHighestLodLocation(location);
	}

}
