#pragma once

#include <string>
#include <map>

// Class used for managing shader information
class CShaderManager {
	// Data
public:
	class CShader {
	public:
		CShader() : ID(0) {};
		unsigned int ID;
		std::string source;
		std::string fileName;
	};

	class CShaderProgram {
	public:
		CShaderProgram() : ID(0) {};
		unsigned int ID;
		std::string friendlyName;
	};

private:
	std::string _lastError;

	std::map<unsigned int, CShaderProgram> _shaderPrograms;
	std::map<std::string, unsigned int> _shaderProgramIDs;

	// Functions
public:
	bool useShaderProgram(unsigned int ID);
	bool useShaderProgram(std::string friendlyName);
	bool createProgramFromFile(std::string friendlyName, CShader &vertexShad, CShader &fragShader);
	unsigned int getIDFromFriendlyName(std::string friendlyName);
	std::string getLastError();

private:
	std::string m_loadSourceFromFile(std::string filename);
	bool m_WasThereACompileError(unsigned int shaderID, std::string &errorText);
};
