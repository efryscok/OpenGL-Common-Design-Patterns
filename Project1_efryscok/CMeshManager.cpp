#include <glad/glad.h>

#include <vector>

#include "CMeshManager.h"

bool CMeshManager::LoadPlyFileIntoGLBuffer(unsigned int programID, std::string plyFile) {
	std::vector<CPlyVertexXYZ> vecPlyVerts;
	std::vector<CPlyTriFace> vecPlyIndices;

	if (!this->_LoadPlyModel(plyFile, vecPlyVerts, vecPlyIndices)) {
		return false;
	}

	float minX, minY, minZ;
	float maxX, maxY, maxZ;

	minX = maxX = vecPlyVerts[0].x;
	minY = maxY = vecPlyVerts[0].y;
	minZ = maxZ = vecPlyVerts[0].z;

	for (std::vector<CPlyVertexXYZ>::iterator IT = vecPlyVerts.begin(); IT != vecPlyVerts.end(); ++IT) {
		if (IT->x < minX) { minX = IT->x; }
		if (IT->y < minY) { minY = IT->y; }
		if (IT->z < minZ) { minZ = IT->z; }

		if (IT->x > maxX) { maxX = IT->x; }
		if (IT->y > maxY) { maxY = IT->y; }
		if (IT->z > maxZ) { maxZ = IT->z; }
	}

	float extentX = maxX - minX;
	float extentY = maxY - minY;
	float extentZ = maxZ - minZ;

	float maxExtent = extentX;
	if (extentY > maxExtent) { maxExtent = extentY; }
	if (extentZ > maxExtent) { maxExtent = extentZ; }

	int numberofVerts = vecPlyVerts.size();
	SVertexXYZRGB* p_vertArray = new SVertexXYZRGB[numberofVerts];

	for (int index = 0; index != numberofVerts; index++) {
		p_vertArray[index].x = vecPlyVerts[index].x;
		p_vertArray[index].y = vecPlyVerts[index].y;
		p_vertArray[index].z = vecPlyVerts[index].z;

		p_vertArray[index].r = 1.0f;
		p_vertArray[index].g = 1.0f;
		p_vertArray[index].b = 1.0f;
	}

	CMeshManager::CVAOInfo tempMeshVAOInfo;
	tempMeshVAOInfo.meshName = plyFile;
	tempMeshVAOInfo.unitScaleValue = 1.0f / maxExtent;

	glGenVertexArrays(1, &(tempMeshVAOInfo.vaoID));
	glBindVertexArray(tempMeshVAOInfo.vaoID);

	GLuint vertex_buffer = 0;
	GLuint index_buffer = 0;

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

	int sizeInBytes = sizeof(SVertexXYZRGB) * numberofVerts;

	glBufferData(GL_ARRAY_BUFFER, sizeInBytes, p_vertArray, GL_STATIC_DRAW);

	glGenBuffers(1, &index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

	int numberOfTriangles = vecPlyIndices.size();
	tempMeshVAOInfo.numberOfIndices = numberOfTriangles * 3;
	int* pIndexArray = new int[tempMeshVAOInfo.numberOfIndices];

	int indexBufferIndex = 0;
	for (size_t triIndex = 0; triIndex != vecPlyIndices.size(); triIndex++, indexBufferIndex += 3) {
		pIndexArray[indexBufferIndex + 0] = vecPlyIndices[triIndex].v1;
		pIndexArray[indexBufferIndex + 1] = vecPlyIndices[triIndex].v2;
		pIndexArray[indexBufferIndex + 2] = vecPlyIndices[triIndex].v3;
	}

	int indexBufferArraySizeInBytes = tempMeshVAOInfo.numberOfIndices * sizeof(int);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferArraySizeInBytes, pIndexArray, GL_STATIC_DRAW);

	int sizeOfVertInBytes = sizeof(SVertexXYZRGB);

	GLuint vpos_location = glGetAttribLocation(programID, "vPosition");
	GLuint vcol_location = glGetAttribLocation(programID, "vColour");

	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeOfVertInBytes, (void*)0);

	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeOfVertInBytes, (void*)(sizeof(float) * 3));

	delete[] p_vertArray;
	delete[] pIndexArray;

	this->_meshVAOInfo[plyFile] = tempMeshVAOInfo;

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
}

bool CMeshManager::LookUpMeshInfo(std::string meshName, unsigned int &vaoID, int &numberOfIndices, float &unitScale) {
	std::map<std::string, CMeshManager::CVAOInfo>::iterator itVAO = this->_meshVAOInfo.find(meshName);

	if (itVAO == this->_meshVAOInfo.end()) {
		return false;
	}

	vaoID = itVAO->second.vaoID;
	numberOfIndices = itVAO->second.numberOfIndices;
	unitScale = itVAO->second.unitScaleValue;

	return true;
}

bool CMeshManager::_LoadPlyModel(std::string filename, std::vector<CPlyVertexXYZ> &vecPlyVerts, std::vector<CPlyTriFace> &vecPlyIndices) {
	FILE* plyFile;
	fopen_s(&plyFile, filename.c_str(), "r");

	char charArray[16];
	
	bool bKeepReading = true;
	while (bKeepReading) {
		fscanf_s(plyFile, "%s", charArray, _countof(charArray));

		if (std::string(charArray) == "vertex") {
			bKeepReading = false;
		}
	}

	int numVertices = 0;
	fscanf_s(plyFile, "%d", &numVertices);
	vecPlyVerts.resize(numVertices);

	bKeepReading = true;
	while (bKeepReading) {
		fscanf_s(plyFile, "%s", charArray, _countof(charArray));

		if (std::string(charArray) == "face") {
			bKeepReading = false;
		}
	}

	int numberOfTriangles = 0;
	fscanf_s(plyFile, "%d", &numberOfTriangles);
	vecPlyIndices.resize(numberOfTriangles);

	bKeepReading = true;
	while (bKeepReading) {
		fscanf_s(plyFile, "%s", charArray, _countof(charArray));

		if (std::string(charArray) == "end_header") {
			bKeepReading = false;
		}
	}

	for (int index = 0; index != numVertices; index++) {
		fscanf_s(plyFile, "%f%f%f", &vecPlyVerts[index].x, &vecPlyVerts[index].y, &vecPlyVerts[index].z);
	}

	for (int index = 0; index != numberOfTriangles; index++) {
		int numIndicesDiscard = 0;
		fscanf_s(plyFile, "%d%d%d%d", &numIndicesDiscard, &vecPlyIndices[index].v1, &vecPlyIndices[index].v2, &vecPlyIndices[index].v3);
	}

	fclose(plyFile);

	return true;
}