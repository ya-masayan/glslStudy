#define _CRT_SECURE_NO_WARNINGS
#include "GLSLProgram.h"
#include <stdio.h>
#include <sys/stat.h>


namespace
{

//! EOF���܂ޕ�������Ԃ�
int getTextSize(const char* fileName)
{
	FILE* file = nullptr;
	file = fopen(fileName, "r");
	// �t�@�C���I�[�v���ł��Ȃ�������A�T�[�g
	assert(file);
	int count = 0;
	while (!feof(file))
	{
		fgetc(file);
		++count;
	}
	fclose(file);
	return count;
}

//! �t�@�C���̒��g��ǂݍ���
//! @param[in] fileName �ǂݍ��ރt�@�C����
//! @param[in] max �ǂݍ��ލő�T�C�Y
//! @param[out] buf �ǂݍ��񂾃f�[�^���i�[����o�b�t�@
//! @param[out] size ���ۂɓǂݍ��񂾃f�[�^�T�C�Y
void read(const char* fileName, int max, void* buf, int* size)
{
	// �t�@�C���I�[�v��
	FILE* file = nullptr;
	file = fopen(fileName, "r");
	assert(file);

	int readSize = 0;
	char* strBuf = reinterpret_cast<char*>(buf);
	for (int i = 0; i<max; ++i)
	{
		strBuf[i] = fgetc(file);
		++readSize;
		if (feof(file))
		{
			break;
		}
	}
	// �I�[�����͎蓮�ł��Ă�����K�v������
	strBuf[readSize - 1] = '\0';
	*size = readSize;
	fclose(file);
}

}

//! �R���X�g���N�^
GLSLProgram::GLSLProgram()
	: handle(0)
	, linked(false)
	, logString("")
{}

//! �V�F�[�_�[�R���p�C��
bool GLSLProgram::compileShaderFromFile(const char* fileName, GLSLShader::GLSLShaderType type)
{
	char*  verText = nullptr;
	int    textSize = 0;
	int    readSize = 0;

	// ���_�V�F�[�_�I�u�W�F�N�g����
	GLuint shader = 0;
	switch(type)
	{
	case GLSLShader::VERTEX:
		shader = glCreateShader(GL_VERTEX_SHADER);
		break;
	case GLSLShader::FRAGMENT:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case GLSLShader::GEOMETRY:
		shader = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case GLSLShader::TESS_CONTROL:
		shader = glCreateShader(GL_TESS_CONTROL_SHADER);
		break;
	case GLSLShader::TESS_EVALUATION:
		shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
		break;
	default:
		assert(false);
		break;
	}

	if (shader == 0)
	{
		// �V�F�[�_�I�u�W�F�N�g�̐����Ɏ��s
		fprintf(stderr, "Shader Create Error\n");
		return false;
	}

	// �V�F�[�_�\�[�X�̕�������擾
	textSize = getTextSize(fileName);
	verText = new char[textSize];
	read(fileName, textSize, verText, &readSize);
	char* codeArray[] = { verText };

	// �R���p�C��
	glShaderSource(shader, 1, codeArray, NULL);
	glCompileShader(shader);
	delete verText;
	verText = nullptr;

	// ���s�����烍�O��f��
	GLint result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		fprintf(stderr, "Failed %s Compile\n", fileName);
		GLint logLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char* log = (char*)malloc(logLen);
			GLsizei written;
			glGetShaderInfoLog(shader, logLen, &written, log);
			logString = log;
			free(log);
		}
		return false;
	}

	// �V�F�[�_�v���O�������쐬����Ă��Ȃ�������쐬
	if(handle == 0)
	{
		handle = glCreateProgram();
		if (handle == 0)
		{
			fprintf(stderr, "Program Object Create Error\n");
			return false;
		}
	}

	// �V�F�[�_���v���O�����I�u�W�F�N�g�ɃA�^�b�`����
	glAttachShader(handle, shader);

	return true;
}

bool GLSLProgram::compileShaderFromString(const std::string& source, GLSLShader::GLSLShaderType type)
{
	char*  verText = nullptr;
	int    textSize = 0;
	int    readSize = 0;

	// ���_�V�F�[�_�I�u�W�F�N�g����
	GLuint shader = 0;
	switch (type)
	{
	case GLSLShader::VERTEX:
		shader = glCreateShader(GL_VERTEX_SHADER);
		break;
	case GLSLShader::FRAGMENT:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case GLSLShader::GEOMETRY:
		shader = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case GLSLShader::TESS_CONTROL:
		shader = glCreateShader(GL_TESS_CONTROL_SHADER);
		break;
	case GLSLShader::TESS_EVALUATION:
		shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
		break;
	default:
		assert(false);
		break;
	}

	if (shader == 0)
	{
		// �V�F�[�_�I�u�W�F�N�g�̐����Ɏ��s
		fprintf(stderr, "Shader Create Error\n");
		return false;
	}

	// �V�F�[�_�\�[�X�̕�������擾
	const char* codeArray[] = { source.c_str() };

	// �R���p�C��
	glShaderSource(shader, 1, codeArray, NULL);
	glCompileShader(shader);
	delete verText;
	verText = nullptr;

	// ���s�����烍�O��f��
	GLint result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		fprintf(stderr, "Failed Shader Compile\n");
		GLint logLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char* log = (char*)malloc(logLen);
			GLsizei written;
			glGetShaderInfoLog(shader, logLen, &written, log);
			logString = log;
			free(log);
		}
		return false;
	}

	// �V�F�[�_�v���O�������쐬����Ă��Ȃ�������쐬
	if (handle == 0)
	{
		handle = glCreateProgram();
		if (handle == 0)
		{
			fprintf(stderr, "Program Object Create Error\n");
			return false;
		}
	}

	// �V�F�[�_���v���O�����I�u�W�F�N�g�ɃA�^�b�`����
	glAttachShader(handle, shader);

	return true;
}


//! �V�F�[�_�[�����N
bool GLSLProgram::link()
{
	// �v���O�����������N����
	glLinkProgram(handle);
	GLint status;
	glGetProgramiv(handle, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		fprintf(stderr, "Failed Shader Program Link\n");
		GLint logLen;
		glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char* log = (char*)malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(handle, logLen, &written, log);
			logString = log;
			free(log);
		}
		return false;
	}
	linked = true;
	return true;
}

//! �V�F�[�_�[�����p����
void GLSLProgram::use()
{
	if(linked)
	{
		glUseProgram(handle);
	}
}

//! ���O���o�͂���
std::string GLSLProgram::log()
{
	return logString;
}

//! �n���h�����擾
int GLSLProgram::getHandle()
{
	return handle;
}

//! ���łɃ����N����Ă��邩
bool GLSLProgram::isLinked()
{
	return linked;
}

//! ���_������Location���o�C���h����
void GLSLProgram::bindAttribLocation(GLuint location, const char* name)
{
	// ���_�����Ɠ��͕ϐ��̊Ԃ̃}�b�s���O���`
	//! @note: ���_�V�F�[�_�̃\�[�X��layout(location=x) ���L�q���Ă����
	//! glBindAttribLocation���L�q����K�v�͂Ȃ�
	glBindAttribLocation(handle, location, name);
}

void GLSLProgram::bindFragDataLocation(GLuint location, const char* name)
{
	glBindFragDataLocation(handle, location, name);
}

// ���j�t�H�[���ϐ����Z�b�g����
void GLSLProgram::setUniform(const char* name, float x, float y, float z)
{
	GLint location = getUniformLocation(name);
	if(location >= 0)
	{
		glUniform3f(location, x, y, z);
	}
}

void GLSLProgram::setUniform(const char* name, const vec3& v)
{
	GLint location = getUniformLocation(name);
	if (location >= 0)
	{
		glUniform3f(location, v.x, v.y, v.z);
	}
}

void GLSLProgram::setUniform(const char* name, const vec4& v)
{
	GLint location = getUniformLocation(name);
	if (location >= 0)
	{
		glUniform4f(location, v.w, v.x, v.y, v.z);
	}
}

void GLSLProgram::setUniform(const char* name, const mat3& m)
{
	GLint location = getUniformLocation(name);
	if (location >= 0)
	{
		glUniformMatrix3fv(location, 1, GL_FALSE, &m[0][0]);
	}
}

void GLSLProgram::setUniform(const char* name, const mat4& m)
{
	GLint location = getUniformLocation(name);
	if (location >= 0)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
	}
}

void GLSLProgram::setUniform(const char* name, float val)
{
	GLint location = getUniformLocation(name);
	if (location >= 0)
	{
		glUniform1f(location, val);
	}
}

void GLSLProgram::setUniform(const char* name, int	val)
{
	GLint location = getUniformLocation(name);
	if (location >= 0)
	{
		glUniform1i(location, val);
	}
}

void GLSLProgram::setUniform(const char* name, bool	val)
{
	GLint location = getUniformLocation(name);
	if (location >= 0)
	{
		glUniform1i(location, val);
	}
}

//! �A�N�e�B�u�ȕϐ����o��
void GLSLProgram::printActiveUniforms()
{
	// �A�N�e�B�u�ȑ����̐��Ɩ��O�̍ő咷�����o��
	GLint maxLength, nAttribs;
	glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &nAttribs);
	glGetProgramiv(handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);

	// �X�̑�������ێ�����o�b�t�@�����蓖�Ă�
	GLchar* name = new char[maxLength];

	// �X�̃A�N�e�B�u�ȑ����ɂ��Ă̏����擾���ăv�����g����
	GLint written, size, location;
	GLenum type;
	printf("  Index  |  name\n");
	for (int i = 0; i<nAttribs; ++i)
	{
		glGetActiveAttrib(handle, i, maxLength, &written, &size, &type, name);
		location = glGetAttribLocation(handle, name);
		printf("  %-5d  |  %s\n", location, name);
	}
	printf("\n");
	delete[] name;
}

void GLSLProgram::printActiveAttribs()
{
	// �A�N�e�B�u�ȑ����̐��Ɩ��O�̍ő咷�����o��
	GLint maxLength, nAttribs;
	glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTES, &nAttribs);
	glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

	// �X�̑�������ێ�����o�b�t�@�����蓖�Ă�
	GLchar* name = new char[maxLength];

	// �X�̃A�N�e�B�u�ȑ����ɂ��Ă̏����擾���ăv�����g����
	GLint written, size, location;
	GLenum type;
	printf("  Index  |  name\n");
	for (int i = 0; i<nAttribs; ++i)
	{
		glGetActiveAttrib(handle, i, maxLength, &written, &size, &type, name);
		location = glGetAttribLocation(handle, name);
		printf("  %-5d  |  %s\n", location, name);
	}
	printf("\n");
	delete[] name;
}

int GLSLProgram::getUniformLocation(const char* name)
{
	return glGetUniformLocation(handle, name);
}

bool GLSLProgram::fileExists(const std::string& fileName)
{
	struct stat st;
	if(stat(fileName.c_str(), &st))
	{
		return true;
	}
	return false;
}
