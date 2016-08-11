#define _CRT_SECURE_NO_WARNINGS

#include "objLoader.h"
#include <stdio.h>

namespace masa{ namespace{

//! objファイル読み込み時最大文字数
const int cStrSize = 256;

//! テキストファイルの行数を取得
int getRowSize(char* fileName)
{
	FILE* file = nullptr;
	file = fopen(fileName, "r");
	// ファイルオープンできなかったらアサート
	assert(file);
	int count = 1;
	while (!feof(file))
	{
		char c = fgetc(file);
		if(c == '\n')
		{
			++count;
		}
	}
	fclose(file);
	return count;
}

}

//! コンストラクタ
ObjLoader::ObjLoader()
	: mVertices(nullptr)
	, mIndices(nullptr)
	, mVertexSize(0)
	, mIndexSize(0)
{}

//! デストラクタ
ObjLoader::~ObjLoader()
{
	if(mVertices)
	{
		delete mVertices;
		mVertices = nullptr;
	}
	if(mIndices)
	{
		delete mIndices;
		mIndices = nullptr;
	}
}

//! objファイルをロード
void ObjLoader::load(char* fileName)
{
	FILE* file = nullptr;
	file = fopen(fileName, "r");
	// ファイルオープンできなかったらアサート
	assert(file);

	char buf[cStrSize];
	char c;
	float v1, v2, v3;
	int vertexdCount = 0;
	int indexCount = 0;

	// 頂点データ、インデックスの数を計算
	while(!feof(file))
	{
		fgets(buf, cStrSize, file);
		sscanf(buf, "%c %f %f %f", &c, &v1, &v2, &v3);
		switch(c)
		{
		case 'v':
			++vertexdCount;
			break;
		case 'f':
			++indexCount;
			break;
		case '\n':
			break;
		default:
			assert(false);
			break;
		}
	}

	fclose(file);

	// 頂点データ、インデックスを格納する
	mVertices = new glm::vec3[vertexdCount];
	mIndices = new glm::uvec3[indexCount];
	mVertexSize = vertexdCount;
	mIndexSize = indexCount;

	// 代入のためリセット
	vertexdCount = 0;
	indexCount = 0;

	file = fopen(fileName, "r");
	// 頂点データ、インデックスの数を計算
	while (!feof(file))
	{
		fgets(buf, cStrSize, file);
		sscanf(buf, "%c %f %f %f", &c, &v1, &v2, &v3);
		switch (c)
		{
		case 'v':
			mVertices[vertexdCount] = glm::vec3(v1, v2, v3);
			++vertexdCount;
			break;
		case 'f':
			mIndices[indexCount] = glm::uvec3(static_cast<unsigned int>(v1), static_cast<unsigned int>(v2), static_cast<unsigned int>(v3));
			++indexCount;
			break;
		case '\n':
			break;
		default:
			assert(false);
			break;
		}
	}

	fclose(file);
	return;

}

}
