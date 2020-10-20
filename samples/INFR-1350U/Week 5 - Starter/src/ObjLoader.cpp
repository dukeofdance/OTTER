#include "ObjLoader.h"

#include<algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

// Borrowed from https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
#pragma region String Trimming

// trim from start (in place)
static inline void ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
		}));
}

// trim from end (in place)
static inline void rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s) {
	ltrim(s);
	rtrim(s);
}

#pragma endregion 

bool ObjLoader::LoadFromFile(const std::string& filename, std::vector<glm::vec3>& out_V, std::vector<glm::vec2>& out_UV, std::vector<glm::vec3>& out_N)
{
    std::vector<GLuint> vIndex, nIndex, uIndex;
    std::vector<glm::vec3> verticies, normals;
    std::vector<glm::vec2> uvs;

    // Open our file in binary mode
    std::ifstream file;
    file.open(filename, std::ios::binary);

    // If our file fails to open, we will throw an error
    if (!file) {
        throw std::runtime_error("File failed to open");
    }

    std::string line;

    //To load from the file
    while (std::getline(file, line)) {
        trim(line);
        if (line.substr(0, 1) == "#")
        {
            //Do nothing becasue # is a comment
        }
        else if (line.substr(0, 2) == "v ")
        {

            std::istringstream ss = std::istringstream(line.substr(2));
            glm::vec3 pos;
            ss >> pos.x >> pos.y >> pos.z;
            verticies.push_back(pos);
        }
        else if (line.substr(0, 2) == "vt")
        {
            std::istringstream ss = std::istringstream(line.substr(2));
            glm::vec2 uv;
            ss >> uv.x >> uv.y;
            uvs.push_back(uv);
        }
        else if (line.substr(0, 2) == "vn")
        {
            std::istringstream ss = std::istringstream(line.substr(2));
            glm::vec3 norm;
            ss >> norm.x >> norm.y >> norm.z;
            normals.push_back(norm);
        }
        else if (line.substr(0, 2) == "f ")
        {
            std::istringstream ss = std::istringstream(line.substr(2));
            char t;
            int v, uv, n;

            for (int i = 0; i < 3; i++)
            {
                ss >> v >> t >> uv >> t >> n;
                vIndex.push_back(v);
                uIndex.push_back(uv);
                nIndex.push_back(n);
            }
        }
    }

    for (unsigned int i = 0; i < vIndex.size(); i++) {

        unsigned int vertexIndex = vIndex[i];
        unsigned int uvIndex = uIndex[i];
        unsigned int normalIndex = nIndex[i];
        glm::vec3 vertex = verticies[vertexIndex - 1];
        glm::vec2 uv = uvs[uvIndex - 1];
        glm::vec3 normal = normals[normalIndex - 1];
        out_V.push_back(vertex);
        out_UV.push_back(uv);
        out_N.push_back(normal);
    }

    return true;
}
