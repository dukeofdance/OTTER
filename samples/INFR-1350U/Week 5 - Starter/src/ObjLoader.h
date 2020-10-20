#pragma once

#include "MeshBuilder.h"
#include "MeshFactory.h"

class ObjLoader
{
public:
	 static bool LoadFromFile(const std::string& filename, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals);

protected:
	ObjLoader() = default;
	~ObjLoader() = default;
}; 
