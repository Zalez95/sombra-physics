#include <sphys/collision/HalfEdgeMesh.h>

sphys::HalfEdgeMesh createTestPolyhedron1();
sphys::HalfEdgeMesh createTestPolyhedron2();
sphys::HalfEdgeMesh createTestPolyhedron3();
std::pair<sphys::HalfEdgeMesh, stdext::ReleaseVector<glm::vec3>> createTestMesh1();
std::pair<sphys::HalfEdgeMesh, stdext::ReleaseVector<glm::vec3>> createTestMesh2();
std::vector<sphys::HalfEdgeMesh> createTestMesh3();
std::pair<sphys::HalfEdgeMesh, stdext::ReleaseVector<glm::vec3>> createTestMesh4();
sphys::HalfEdgeMesh createTestMesh5();
std::vector<sphys::HalfEdgeMesh> createTestMesh6();
sphys::HalfEdgeMesh createTestPlane1();
sphys::HalfEdgeMesh createTestPlane2();
sphys::HalfEdgeMesh createTestTube1();
std::vector<sphys::HalfEdgeMesh> createTestTube2();
std::pair<std::vector<glm::vec3>, std::vector<unsigned short>> createTestTriangleMesh();
