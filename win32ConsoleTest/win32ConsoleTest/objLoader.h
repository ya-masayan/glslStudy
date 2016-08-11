#pragma once

// obj�t�@�C�������[�h����N���X
#include <glm/vec3.hpp>

namespace masa { namespace{}

class ObjLoader
{
public:
	//! �R���X�g���N�^
	ObjLoader();

	//! �f�X�g���N�^
	~ObjLoader();

	//! obj�t�@�C�������[�h1
	void load(char* fileName);

	//! ���_�f�[�^���擾
	float* getVetices(){ return &(mVertices[0][0]); }

	//! ���_�f�[�^�T�C�Y���擾
	int getVerticesSize(){ return mVertexSize; }

	//! ���_�C���f�b�N�X���擾
	unsigned int* getIndices(){ return &(mIndices[0][0]); }

	//! ���_�C���f�b�N�X�T�C�Y���擾
	int getIndicesSize(){ return mIndexSize; }

private:
	glm::vec3* mVertices; //!< ���_�f�[�^
	glm::uvec3* mIndices;  //!< ���_�C���f�b�N�X
	int mVertexSize;		  //!< ���_�f�[�^�T�C�Y
	int mIndexSize;		  //!< ���_�C���f�b�N�X�T�C�Y
};

}
