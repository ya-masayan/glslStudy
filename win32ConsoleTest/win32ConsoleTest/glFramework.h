#pragma once

#include "GLSLProgram.h"
#include "objLoader.h"
#include "attribImporter.h"
#include <list>

//! �O���錾
class Camera;
class Viewport;
class ModelCube;

//! �V���O���g��
class GlFramework
{
public:
	struct InitArg
	{
		int argc;
		char** argv;
	};

public:
	//! �C���X�^���X�𐶐�
	static GlFramework* createInstance();

	//! �C���X�^���X��j��
	static void deleteInstance();

	//! �C���X�^���X���擾
	static GlFramework* getInstance();

	//! ������
	void initialize( InitArg& arg );

	//! �I��
	void finalize();

	//! ���C�����[�v
	void mainLoop();

private:
	//! �R���X�g���N�^
	GlFramework()
		: m_pViewport( nullptr )
		, m_WindowSize( 0.f, 0.f )
	{
		m_pCube[0] = nullptr;
		m_pCube[1] = nullptr;
	}

	//! �f�X�g���N�^
	~GlFramework()
	{}

	//! ��ʃT�C�Y�ύX���֐�
	static void resize_( int w, int h );

	//! �`��
	static void display_();

	//! �X�V
	static void idle_();

	//! �}�E�X����
	static void mouse_( int button, int state, int x, int y );

	//! �L�[�{�[�h����
	static void keyboard_( unsigned char key, int x, int y );

private:
	static GlFramework*		m_pInstance;
	std::list< Camera* >	m_CameraList;
	Viewport*				m_pViewport; //!< ��
	ModelCube*				m_pCube[2];	 //!< ��
	masa::ObjLoader			m_TeaPot;
	masa::AttribImporter	m_Attribute;

	GLSLProgram				m_GlslProgram;
	glm::vec2				m_WindowSize;
    // �Ƃ肠�������͂܂��J������1�����ł���
    Camera*                 m_pCamera;
};