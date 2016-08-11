#pragma once
#include <GL/glew.h>

namespace masa{ namespace{}

class AttribImporter
{
public:
	//! �R���X�g���N�^
	AttribImporter();
	~AttribImporter();

	//! ������
	void initialize();

	//! ���_������ǉ�
	void addAttrib( const float* data, int size, int index);

    //! ���_�C���f�b�N�X��ǉ�
    void addIndice( const int* data, int size );
    void addIndice( const unsigned int* data, int size )
    {
        addIndice( reinterpret_cast<const int*>(data), size );
    }

	//! ���_�C���f�b�N�X���w��
	void setIndice(unsigned int* data, int size);

	//! �`��
	void draw();

private:
	GLuint mVaoHandle;	//! ���_�z��I�u�W�F�N�g�n���h��
	unsigned int* mIndice;	//! ���_�C���f�b�N�X
	int mIndiceSize;
};

}
