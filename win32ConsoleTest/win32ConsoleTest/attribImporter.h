#pragma once
#include <GL/glew.h>

namespace masa{ namespace{}

class AttribImporter
{
public:
	//! コンストラクタ
	AttribImporter();
	~AttribImporter();

	//! 初期化
	void initialize();

	//! 頂点属性を追加
	void addAttrib( const float* data, int size, int index);

    //! 頂点インデックスを追加
    void addIndice( const int* data, int size );
    void addIndice( const unsigned int* data, int size )
    {
        addIndice( reinterpret_cast<const int*>(data), size );
    }

	//! 頂点インデックスを指定
	void setIndice(unsigned int* data, int size);

	//! 描画
	void draw();

private:
	GLuint mVaoHandle;	//! 頂点配列オブジェクトハンドル
	unsigned int* mIndice;	//! 頂点インデックス
	int mIndiceSize;
};

}
