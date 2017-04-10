#pragma once

#include <string>
#include <vector>
#include <map>

struct SVertexXYZRGB {
	float x, y, z;
	float r, g, b;
};

// Used to store the vertex locations read from ply file
struct CPlyVertexXYZ {
	CPlyVertexXYZ() : x(0.0f), y(0.0f), z(0.0f) {}
	float x;
	float y;
	float z;
};

// Used to store the indice numbers read from ply file
struct CPlyTriFace {
	CPlyTriFace() : v1(-1), v2(-1), v3(-1) {}
	int v1;
	int v2;
	int v3;
};

// Class for managing mesh information for many meshs
class CMeshManager {
	// Data
private:
	struct CVAOInfo {
		CVAOInfo() : vaoID(0), numberOfIndices(0), unitScaleValue(1.0f) {}
		std::string meshName;
		unsigned int vaoID;
		unsigned int numberOfIndices;
		float unitScaleValue;
	};

	std::map<std::string, CVAOInfo> _meshVAOInfo;

	// Functions
public:
	bool LoadPlyFileIntoGLBuffer(unsigned int programID, std::string plyFile);
	bool LookUpMeshInfo(std::string meshName, unsigned int &vaoID, int &numberOfIndices, float &unitScale);

private:
	bool _LoadPlyModel(std::string filename, std::vector<CPlyVertexXYZ> &vecPlyVerts, std::vector<CPlyTriFace> &vecPlyIndices);
};
