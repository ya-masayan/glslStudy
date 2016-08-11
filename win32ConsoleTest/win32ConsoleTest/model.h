#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

class Model
{
public:
	struct InitArg
	{};

public:
	//! �R���X�g���N�^
	Model()
		//: m_pVertex( nullptr )
		//, m_pVertexColor( nullptr )
		//, m_pVertexFace( nullptr )
		//, m_VertexSize( -1 )
		: m_Pos( 0.f, 0.f, 0.f )
		, m_Rotate( 0.f, 1.f, 0.f, 0.f )
		, m_Scale( 1.f, 1.f, 1.f )
	{}

	//! �f�X�g���N�^
	~Model()
	{}

	//! ������
	void initialize( InitArg& arg );

	//! �I��
	void finalize();

	//! �`��
	void draw();

	//! �ʒu��ݒ�
	void setPos( const glm::vec3& pos ){ m_Pos = pos; }
	//! �ʒu���擾
	const glm::vec3& getPos(){ return m_Pos; }

	//! ��]��ݒ�
	void setRotate( const glm::vec4& rotate ){ m_Rotate = rotate; }
	//! ��]���擾
	const glm::vec4& getRotate(){ return m_Rotate; }

	//! �k�ڂ�ݒ�
	void setScale( const glm::vec3& scale ){ m_Scale = scale; }
	//! �k�ڂ��擾
	const glm::vec3& getScale(){ return m_Scale; }

protected:
	//! �p���p
	virtual void doInitialize_( InitArg& arg ) = 0;
	virtual void doFinalize_() = 0;
	virtual void doDraw_() = 0;

private:
	//const GLdouble* m_pVertex;
	//const GLdouble** m_pVertexColor;
	//int** m_pVertexFace;
	//int m_VertexSize;
	glm::vec3 m_Pos;
	glm::vec4 m_Rotate; //!< x,y,z��axis, w��angle
	glm::vec3 m_Scale;
};
