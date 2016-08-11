#pragma once

// objファイルをロードするクラス
#include <glm/vec3.hpp>

namespace masa { namespace{}

class ObjLoader
{
public:
	//! コンストラクタ
	ObjLoader();

	//! デストラクタ
	~ObjLoader();

	//! objファイルをロード1
	void load(char* fileName);

	//! 頂点データを取得
	float* getVetices(){ return &(mVertices[0][0]); }

	//! 頂点データサイズを取得
	int getVerticesSize(){ return mVertexSize; }

	//! 頂点インデックスを取得
	unsigned int* getIndices(){ return &(mIndices[0][0]); }

	//! 頂点インデックスサイズを取得
	int getIndicesSize(){ return mIndexSize; }

private:
	glm::vec3* mVertices; //!< 頂点データ
	glm::uvec3* mIndices;  //!< 頂点インデックス
	int mVertexSize;		  //!< 頂点データサイズ
	int mIndexSize;		  //!< 頂点インデックスサイズ
};

}
