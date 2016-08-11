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
	//! コンストラクタ
	GLSLProgram();

	//! シェーダーコンパイル
	bool compileShaderFromFile	(const char* fileName	  , GLSLShader::GLSLShaderType type);
	bool compileShaderFromString(const std::string& source, GLSLShader::GLSLShaderType type);

	//! シェーダーリンク
	bool link();

	//! シェーダーを私用する
	void use();

	//! ログを出力する
	std::string log();

	//! ハンドルを取得
	int getHandle();
	
	//! すでにリンクされているか
	bool isLinked();

	//! 頂点属性とLocationをバインドする
	void bindAttribLocation	 (GLuint location, const char* name);
	void bindFragDataLocation(GLuint location, const char* name);

	// ユニフォーム変数をセットする
	void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, const vec3& v);
	void setUniform(const char* name, const vec4& v);
	void setUniform(const char* name, const mat3& m);
	void setUniform(const char* name, const mat4& m);
	void setUniform(const char* name, float val);
	void setUniform(const char* name, int	val);
	void setUniform(const char* name, bool	val);

	//! アクティブな変数を出力
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
