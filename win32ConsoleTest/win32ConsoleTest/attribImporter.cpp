#include "attribImporter.h"
#include <GL/glut.h>

extern GLuint  vaoHandle;


namespace masa{ namespace{}

AttribImporter::AttribImporter()
	: mIndice(nullptr)
{}

AttribImporter::~AttribImporter()
{
	if( mIndice )
	{
		delete[] mIndice;
	}
}

//! ������
void AttribImporter::initialize()
{
	// ���_�z��I�u�W�F�N�g�̍쐬�Ɛݒ�
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);
}

//! ���_������ǉ�
void AttribImporter::addAttrib( const float* data, int size, int index)
{
	GLuint vboHandle;
	// �o�b�t�@�I�u�W�F�N�g����
	glGenBuffers(1, &vboHandle);
	// �o�b�t�@�I�u�W�F�N�g�Ƀf�[�^�𓊓�
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);
	// �C���f�b�N�X�ƃo�b�t�@�ɑΉ��Â���
    // MEMO: ��2�����͊�{��vec3������Ƒz�肷��
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)nullptr);

    // ���_������L���ɂ���
    glEnableVertexAttribArray( index );
}

//! ���_�C���f�b�N�X��ǉ�
void
AttribImporter::addIndice( const int* data, int size )
{
    GLuint iboHandle;
    glGenBuffers( 1, &iboHandle );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, iboHandle );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, size * sizeof( int ), data, GL_STATIC_DRAW );
    mIndiceSize = size;
}

//! ���_�C���f�b�N�X���w��
void AttribImporter::setIndice(unsigned int* data, int size)
{
	if(!mIndice)
	{
		return;
	}

	mIndiceSize = size;
	mIndice = new unsigned int[size];
	for(int i=0; i<size; ++i)
	{
		mIndice[i] = data[i];
	}
}


//! �`��
void AttribImporter::draw()
{
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements( GL_TRIANGLES, mIndiceSize, GL_UNSIGNED_INT, 0 );
}

}
