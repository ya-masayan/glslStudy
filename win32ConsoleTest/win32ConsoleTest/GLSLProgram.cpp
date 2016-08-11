#define _CRT_SECURE_NO_WARNINGS
#include "GLSLProgram.h"
#include <stdio.h>
#include <sys/stat.h>


namespace
{

//! EOFを含む文字数を返す
int getTextSize(const char* fileName)
{
	FILE* file = nullptr;
	file = fopen(fileName, "r");
	// ファイルオープンできなかったらアサート
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

//! ファイルの中身を読み込む
//! @param[in] fileName 読み込むファイル名
//! @param[in] max 読み込む最大サイズ
//! @param[out] buf 読み込んだデータを格納するバッファ
//! @param[out] size 実際に読み込んだデータサイズ
void read(const char* fileName, int max, void* buf, int* size)
{
	// ファイルオープン
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
	// 終端文字は手動でつけてあげる必要がある
	strBuf[readSize - 1] = '\0';
	*size = readSize;
	fclose(file);
}

}

//! コンストラクタ
GLSLProgram::GLSLProgram()
	: handle(0)
	, linked(false)
	, logString("")
{}

//! シェーダーコンパイル
bool GLSLProgram::compileShaderFromFile(const char* fileName, GLSLShader::GLSLShaderType type)
{
	char*  verText = nullptr;
	int    textSize = 0;
	int    readSize = 0;

	// 頂点シェーダオブジェクト生成
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
		// シェーダオブジェクトの生成に失敗
		fprintf(stderr, "Shader Create Error\n");
		return false;
	}

	// シェーダソースの文字列を取得
	textSize = getTextSize(fileName);
	verText = new char[textSize];
	read(fileName, textSize, verText, &readSize);
	char* codeArray[] = { verText };

	// コンパイル
	glShaderSource(shader, 1, codeArray, NULL);
	glCompileShader(shader);
	delete verText;
	verText = nullptr;

	// 失敗したらログを吐く
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

	// シェーダプログラムが作成されていなかったら作成
	if(handle == 0)
	{
		handle = glCreateProgram();
		if (handle == 0)
		{
			fprintf(stderr, "Program Object Create Error\n");
			return false;
		}
	}

	// シェーダをプログラムオブジェクトにアタッチする
	glAttachShader(handle, shader);

	return true;
}

bool GLSLProgram::compileShaderFromString(const std::string& source, GLSLShader::GLSLShaderType type)
{
	char*  verText = nullptr;
	int    textSize = 0;
	int    readSize = 0;

	// 頂点シェーダオブジェクト生成
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
		// シェーダオブジェクトの生成に失敗
		fprintf(stderr, "Shader Create Error\n");
		return false;
	}

	// シェーダソースの文字列を取得
	const char* codeArray[] = { source.c_str() };

	// コンパイル
	glShaderSource(shader, 1, codeArray, NULL);
	glCompileShader(shader);
	delete verText;
	verText = nullptr;

	// 失敗したらログを吐く
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

	// シェーダプログラムが作成されていなかったら作成
	if (handle == 0)
	{
		handle = glCreateProgram();
		if (handle == 0)
		{
			fprintf(stderr, "Program Object Create Error\n");
			return false;
		}
	}

	// シェーダをプログラムオブジェクトにアタッチする
	glAttachShader(handle, shader);

	return true;
}


//! シェーダーリンク
bool GLSLProgram::link()
{
	// プログラムをリンクする
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

//! シェーダーを私用する
void GLSLProgram::use()
{
	if(linked)
	{
		glUseProgram(handle);
	}
}

//! ログを出力する
std::string GLSLProgram::log()
{
	return logString;
}

//! ハンドルを取得
int GLSLProgram::getHandle()
{
	return handle;
}

//! すでにリンクされているか
bool GLSLProgram::isLinked()
{
	return linked;
}

//! 頂点属性とLocationをバインドする
void GLSLProgram::bindAttribLocation(GLuint location, const char* name)
{
	// 頂点属性と入力変数の間のマッピングを定義
	//! @note: 頂点シェーダのソースにlayout(location=x) を記述していれば
	//! glBindAttribLocationを記述する必要はない
	glBindAttribLocation(handle, location, name);
}

void GLSLProgram::bindFragDataLocation(GLuint location, const char* name)
{
	glBindFragDataLocation(handle, location, name);
}

// ユニフォーム変数をセットする
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

//! アクティブな変数を出力
void GLSLProgram::printActiveUniforms()
{
	// アクティブな属性の数と名前の最大長を取り出す
	GLint maxLength, nAttribs;
	glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &nAttribs);
	glGetProgramiv(handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);

	// 個々の属性名を保持するバッファを割り当てる
	GLchar* name = new char[maxLength];

	// 個々のアクティブな属性についての情報を取得してプリントする
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
	// アクティブな属性の数と名前の最大長を取り出す
	GLint maxLength, nAttribs;
	glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTES, &nAttribs);
	glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);

	// 個々の属性名を保持するバッファを割り当てる
	GLchar* name = new char[maxLength];

	// 個々のアクティブな属性についての情報を取得してプリントする
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
