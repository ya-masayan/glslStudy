#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

namespace GLSLShader
{

enum GLSLShaderType
{
	VERTEX,
	FRAGMENT,
	GEOMETRY,
	TESS_CONTROL,
	TESS_EVALUATION
};
}

class GLSLProgram
{
public:
	//! �R���X�g���N�^
	GLSLProgram();

	//! �V�F�[�_�[�R���p�C��
	bool compileShaderFromFile	(const char* fileName	  , GLSLShader::GLSLShaderType type);
	bool compileShaderFromString(const std::string& source, GLSLShader::GLSLShaderType type);

	//! �V�F�[�_�[�����N
	bool link();

	//! �V�F�[�_�[�����p����
	void use();

	//! ���O���o�͂���
	std::string log();

	//! �n���h�����擾
	int getHandle();
	
	//! ���łɃ����N����Ă��邩
	bool isLinked();

	//! ���_������Location���o�C���h����
	void bindAttribLocation	 (GLuint location, const char* name);
	void bindFragDataLocation(GLuint location, const char* name);

	// ���j�t�H�[���ϐ����Z�b�g����
	void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, const vec3& v);
	void setUniform(const char* name, const vec4& v);
	void setUniform(const char* name, const mat3& m);
	void setUniform(const char* name, const mat4& m);
	void setUniform(const char* name, float val);
	void setUniform(const char* name, int	val);
	void setUniform(const char* name, bool	val);

	//! �A�N�e�B�u�ȕϐ����o��
	void printActiveUniforms();
	void printActiveAttribs();

private:
	int getUniformLocation(const char* name);
	bool fileExists(const std::string& fileName);

private:
	int handle;
	bool linked;
	std::string logString;
};
