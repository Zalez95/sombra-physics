#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include "../../graphics/3D/Mesh.h"
#include "../../collision/HalfEdgeMesh.h"
#include "../graphics/RawMesh.h"

namespace se::app {

	/**
	 * Class MeshLoader, it's used for creating meshes from raw meshes data
	 */
	class MeshLoader
	{
	public:		// Functions
		/** creates a Graphics Mesh with the given mesh data
		 *
		 * @param	rawMesh the data with which we will create the graphics
		 *			mesh
		 * @return	the new Graphics Mesh */
		static graphics::Mesh createGraphicsMesh(const RawMesh& rawMesh);

		/** Creates a HalfEdgeMesh with the given mesh data
		 *
		 * @param	rawMesh the data with which we will create the HalfEdgeMesh
		 * @return	a pair with the loaded HafEdgeMesh and a bool that indicates
		 *			if the HalfEdgeMesh was loaded correctly or not */
		static std::pair<collision::HalfEdgeMesh, bool> createHalfEdgeMesh(
			const RawMesh& rawMesh
		);

		/** Creates a RawMesh from the given HalfEdgeMesh
		 *
		 * @param	heMesh the original HalfEdgeMesh to create the RawMEsh from
		 * @param	normals the normal vectors of the heMesh faces
		 * @return	a pair with the created RawMesh and a bool that indicates
		 *			if the HalfEdgeMesh was loaded correctly or not */
		static std::pair<RawMesh, bool> createRawMesh(
			const collision::HalfEdgeMesh& heMesh,
			const utils::PackedVector<glm::vec3>& normals
		);

		/** Creates a Box mesh from the given data. The generated RawMesh
		 * will only have setted the positions, uvs and face indices.
		 *
		 * @param	name the name of the mesh
		 * @param	lengths the length of each axis of the Box
		 * @return	the new RawMesh */
		static RawMesh createBoxMesh(
			const std::string& name, glm::vec3 lengths
		);

		/** Creates a Sphere mesh from the given data. The generated RawMesh
		 * will only have setted the positions and face indices.
		 *
		 * @param	name the name of the mesh
		 * @param	segments the number of segments of the Sphere mesh
		 * @param	rings the number of rings of the Sphere mesh
		 * @param	radius the radius of the sphere mesh
		 * @return	the new RawMesh */
		static RawMesh createSphereMesh(
			const std::string& name,
			std::size_t segments, std::size_t rings, float radius
		);

		/** Creates a Dome mesh from the given data. The generated RawMesh
		 * will only have setted the positions and face indices.
		 *
		 * @param	name the name of the mesh
		 * @param	segments the number of segments of the Dome mesh
		 * @param	rings the number of rings of the Dome mesh
		 * @param	radius the radius of the Dome mesh
		 * @return	the new RawMesh */
		static RawMesh createDomeMesh(
			const std::string& name,
			std::size_t segments, std::size_t rings, float radius
		);

		/** Calculates the Normals of the given vertices
		 *
		 * @param	positions a vector with the positions of the vertices
		 * @param	faceIndices a vector with indices of the vertices that
		 *			compose the triangle faces of a Mesh
		 * @return	a vector with the normals of the vertices */
		static std::vector<glm::vec3> calculateNormals(
			const std::vector<glm::vec3>& positions,
			const std::vector<unsigned short>& faceIndices
		);

		/** Calculates the Tangents of the given vertices
		 *
		 * @param	positions a vector with the positions of the vertices
		 * @param	texCoords a vector with the texture coordinates of the
		 *			vertices
		 * @param	faceIndices a vector with indices of the vertices that
		 *			compose the triangle faces of a Mesh
		 * @return	a vector with the tangents of the vertices */
		static std::vector<glm::vec3> calculateTangents(
			const std::vector<glm::vec3>& positions,
			const std::vector<glm::vec2>& texCoords,
			const std::vector<unsigned short>& faceIndices
		);
	};

}

#endif		// MESH_LOADER_H
