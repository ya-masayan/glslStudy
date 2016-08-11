#define _CRT_SECURE_NO_WARNINGS

#include "objLoader.h"
#include <stdio.h>

namespace masa{ namespace{

//! obj�t�@�C���ǂݍ��ݎ��ő啶����
const int cStrSize = 256;

//! �e�L�X�g�t�@�C���̍s�����擾
int getRowSize(char* fileName)
{
	FILE* file = nullptr;
	file = fopen(fileName, "r");
	// �t�@�C���I�[�v���ł��Ȃ�������A�T�[�g
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

//! �R���X�g���N�^
ObjLoader::ObjLoader()
	: mVertices(nullptr)
	, mIndices(nullptr)
	, mVertexSize(0)
	, mIndexSize(0)
{}

//! �f�X�g���N�^
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

//! obj�t�@�C�������[�h
void ObjLoader::load(char* fileName)
{
	FILE* file = nullptr;
	file = fopen(fileName, "r");
	// �t�@�C���I�[�v���ł��Ȃ�������A�T�[�g
	assert(file);

	char buf[cStrSize];
	char c;
	float v1, v2, v3;
	int vertexdCount = 0;
	int indexCount = 0;

	// ���_�f�[�^�A�C���f�b�N�X�̐����v�Z
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

	// ���_�f�[�^�A�C���f�b�N�X���i�[����
	mVertices = new glm::vec3[vertexdCount];
	mIndices = new glm::uvec3[indexCount];
	mVertexSize = vertexdCount;
	mIndexSize = indexCount;

	// ����̂��߃��Z�b�g
	vertexdCount = 0;
	indexCount = 0;

	file = fopen(fileName, "r");
	// ���_�f�[�^�A�C���f�b�N�X�̐����v�Z
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
