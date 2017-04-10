#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "CShaderManager.h"

bool CShaderManager::useShaderProgram(unsigned int ID) {
	glUseProgram(ID);
	return true;
}

bool CShaderManager::useShaderProgram(std::string friendlyName) {
	std::map<std::string, unsigned int>::iterator
		itShad = this->_shaderProgramIDs.find(friendlyName);

	if (itShad == this->_shaderProgramIDs.end()) {
		return false;
	}
	glUseProgram(itShad->second);

	return true;
}

unsigned int CShaderManager::getIDFromFriendlyName(std::string friendlyName) {
	std::map<std::string, unsigned int>::iterator
		itShad = this->_shaderProgramIDs.find(friendlyName);

	if (itShad == this->_shaderProgramIDs.end()) {
		return 0;
	}
	return itShad->second;
}

std::string CShaderManager::m_loadSourceFromFile(std::string filename) {
	std::ifstream theFile(filename.c_str());

	std::stringstream ssSource;
	std::string temp;

	while (theFile >> temp) {
		ssSource << temp << " ";
	}

	theFile.close();
	return ssSource.str();
}

bool CShaderManager::m_WasThereACompileError(unsigned int shaderID,	std::string &errorText) {
	errorText = "";

	GLint isCompiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		char* pLogText = new char[maxLength];
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, pLogText);

		errorText.append(pLogText);
		return true;
	}
	return false;
}

std::string CShaderManager::getLastError(void) {
	std::string lastErrorTemp = this->_lastError;
	this->_lastError = "";
	return lastErrorTemp;
}

bool CShaderManager::createProgramFromFile(std::string friendlyName, CShader &vertexShad, CShader &fragShader) {
	vertexShad.ID = glCreateShader(GL_VERTEX_SHADER);
	vertexShad.source = this->m_loadSourceFromFile(vertexShad.fileName);

	const char* tempVertChar = vertexShad.source.c_str();

	glShaderSource(vertexShad.ID, 1, &tempVertChar, NULL);
	glCompileShader(vertexShad.ID);

	delete tempVertChar;

	std::string errorText = "";
	if (this->m_WasThereACompileError(vertexShad.ID, errorText)) {
		std::stringstream ssError;
		ssError << "Vertex shader compile error: ";
		ssError << errorText;
		this->_lastError = ssError.str();
		return false;
	}

	fragShader.ID = glCreateShader(GL_FRAGMENT_SHADER);
	fragShader.source = this->m_loadSourceFromFile(fragShader.fileName);

	const char* tempFragChar = fragShader.source.c_str();
	glShaderSource(fragShader.ID, 1, &tempFragChar, NULL);
	glCompileShader(fragShader.ID);
	delete tempFragChar;

	if (this->m_WasThereACompileError(vertexShad.ID, errorText)) {
		std::stringstream ssError;
		ssError << "Fragment shader compile error: ";
		ssError << errorText;
		this->_lastError = ssError.str();
		return false;
	}

	CShaderProgram curProgram;
	curProgram.ID = glCreateProgram();

	glAttachShader(curProgram.ID, vertexShad.ID);
	glAttachShader(curProgram.ID, fragShader.ID);
	glLinkProgram(curProgram.ID);

	curProgram.friendlyName = friendlyName;

	this->_shaderPrograms[curProgram.ID] = curProgram;
	this->_shaderProgramIDs[curProgram.friendlyName] = curProgram.ID;

	return true;
}
