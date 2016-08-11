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

//! 初期化
void AttribImporter::initialize()
{
	// 頂点配列オブジェクトの作成と設定
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);
}

//! 頂点属性を追加
void AttribImporter::addAttrib( const float* data, int size, int index)
{
	GLuint vboHandle;
	// バッファオブジェクト生成
	glGenBuffers(1, &vboHandle);
	// バッファオブジェクトにデータを投入
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);
	// インデックスとバッファに対応づける
    // MEMO: 第2引数は基本はvec3が入ると想定する
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)nullptr);

    // 頂点属性を有効にする
    glEnableVertexAttribArray( index );
}

//! 頂点インデックスを追加
void
AttribImporter::addIndice( const int* data, int size )
{
    GLuint iboHandle;
    glGenBuffers( 1, &iboHandle );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, iboHandle );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, size * sizeof( int ), data, GL_STATIC_DRAW );
    mIndiceSize = size;
}

//! 頂点インデックスを指定
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


//! 描画
void AttribImporter::draw()
{
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements( GL_TRIANGLES, mIndiceSize, GL_UNSIGNED_INT, 0 );
}

}
