#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class Model
{
public:
	struct InitArg
	{};

public:
	//! コンストラクタ
	Model()
		//: m_pVertex( nullptr )
		//, m_pVertexColor( nullptr )
		//, m_pVertexFace( nullptr )
		//, m_VertexSize( -1 )
		: m_Pos( 0.f, 0.f, 0.f )
		, m_Rotate( 0.f, 1.f, 0.f, 0.f )
		, m_Scale( 1.f, 1.f, 1.f )
	{}

	//! デストラクタ
	~Model()
	{}

	//! 初期化
	void initialize( InitArg& arg );

	//! 終了
	void finalize();

	//! 描画
	void draw();

	//! 位置を設定
	void setPos( const glm::vec3& pos ){ m_Pos = pos; }
	//! 位置を取得
	const glm::vec3& getPos(){ return m_Pos; }

	//! 回転を設定
	void setRotate( const glm::vec4& rotate ){ m_Rotate = rotate; }
	//! 回転を取得
	const glm::vec4& getRotate(){ return m_Rotate; }

	//! 縮尺を設定
	void setScale( const glm::vec3& scale ){ m_Scale = scale; }
	//! 縮尺を取得
	const glm::vec3& getScale(){ return m_Scale; }

protected:
	//! 継承用
	virtual void doInitialize_( InitArg& arg ) = 0;
	virtual void doFinalize_() = 0;
	virtual void doDraw_() = 0;

private:
	//const GLdouble* m_pVertex;
	//const GLdouble** m_pVertexColor;
	//int** m_pVertexFace;
	//int m_VertexSize;
	glm::vec3 m_Pos;
	glm::vec4 m_Rotate; //!< x,y,zはaxis, wはangle
	glm::vec3 m_Scale;
};
