#include "glFramework.h"

#include "camera.h"
#include "modelManager.h"
#include "modelCube.h"
#include "modelPrimitive.h"
#include <GL/glew.h>
#define GLEW_STATIC
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>
#include <assert.h>

namespace {

//! ���_�f�[�^
const GLdouble vertex[][3] = {
	{ 0.0, 0.0, 0.0 }, /* A */
	{ 1.0, 0.0, 0.0 }, /* B */
	{ 1.0, 1.0, 0.0 }, /* C */
	{ 0.0, 1.0, 0.0 }, /* D */
	{ 0.0, 0.0, 1.0 }, /* E */
	{ 1.0, 0.0, 1.0 }, /* F */
	{ 1.0, 1.0, 1.0 }, /* G */
	{ 0.0, 1.0, 1.0 }  /* H */
};

//! �ʃf�[�^
int face[][4] = {
	{ 0, 1, 2, 3 },
	{ 1, 5, 6, 2 },
	{ 5, 4, 7, 6 },
	{ 4, 0, 3, 7 },
	{ 4, 5, 1, 0 },
	{ 3, 2, 6, 7 }
};

//! �F�f�[�^
GLdouble color[][3] = {
	{ 1.0, 0.0, 0.0 }, /* �� */
	{ 0.0, 1.0, 0.0 }, /* �� */
	{ 0.0, 0.0, 1.0 }, /* �� */
	{ 1.0, 1.0, 0.0 }, /* �� */
	{ 1.0, 0.0, 1.0 }, /* �}�[���^ */
	{ 0.0, 1.0, 1.0 }  /* �V�A�� �@*/
};

} // namespace

GlFramework* GlFramework::m_pInstance = nullptr;
GLuint  vaoHandle;

//! �C���X�^���X�𐶐�
GlFramework*
GlFramework::createInstance()
{
	assert( !m_pInstance );
	m_pInstance = new GlFramework();
	return m_pInstance;
}

//! �C���X�^���X��j��
void
GlFramework::deleteInstance()
{
	assert( m_pInstance );
	delete m_pInstance;
	m_pInstance = nullptr;
}

//! �C���X�^���X���擾
GlFramework*
GlFramework::getInstance()
{
	assert( m_pInstance );
	return m_pInstance;
}

//! ������
void
GlFramework::initialize( InitArg& arg )
{
	glutInitWindowPosition( 100, 100 );
	glutInitWindowSize( 640, 480 );
	glutInit( &( arg.argc ), arg.argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutCreateWindow( arg.argv[0] );
	glewInit();
	glutDisplayFunc( display_ );
	glutReshapeFunc( resize_ );
	glutMouseFunc( mouse_ );
	glutKeyboardFunc( keyboard_ );
    glutIdleFunc( idle_ );


	// �w�i�̐F��ݒ�
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// �f�v�X�o�b�t�@��L���ɂ���
	// �f�v�X�o�b�t�@��L���ɂ���ɂ�3�ӏ��L�q���K�v
	// 1. glutInitDisplayMode��GLUT_DEPTH��ǉ�
	// 2. glEnable( GL_DEPTH_TEST )���L�q
	// 3. glClear�Ŗ��t���[��GL_DEPTH_BUFFER_BIT���w��
	glEnable( GL_DEPTH_TEST );

	// ���ʂ��J�����O����悤�ݒ�
	// �J�����O�ݒ�͂����ɂ���2�s�݂̂ōs����
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	Camera::InitArg camera_arg;
	{
		camera_arg.eye = glm::vec3( 0.0, 0.0, 10.0 );
		camera_arg.at = glm::vec3( 0.0, 0.0, 0.0 );
	}
	Camera* camera = new Camera( camera_arg );
	m_CameraList.push_back( camera );
    m_pCamera = camera;

	Viewport::ViewportInfo view_info;
	{
		view_info.pos = glm::vec2( 0.f, 0.f );
		view_info.size = glm::vec2( 100.f, 100.f );
	}
	m_pViewport = camera->addViewport( view_info );
	//m_pViewport->setAdjustWindowSize( true );
	m_pViewport->setCoordType( Viewport::eRelative );
	{
		view_info.pos = glm::vec2( 0.f, 0.f );
		view_info.size = glm::vec2( 1.f, 1.f );
	}
	m_pViewport->setViewport( view_info );

	// Model�֘A��������
	ModelManager::createInstance();
	{
		m_pCube[0] = new ModelCube();
		ModelManager::getInstance()->addModel( m_pCube[0] );
		m_pCube[1] = new ModelCube();
		m_pCube[1]->setPos( glm::vec3( 1.f, 1.f, 0.f ) );
		ModelManager::getInstance()->addModel( m_pCube[1] );

		// TeaPot�ǉ�
		m_TeaPot.load( "teapot.obj" );
	}

	// �V�F�[�_�I�u�W�F�N�g�쐬
	m_GlslProgram.compileShaderFromFile( "basic_basic.vert", GLSLShader::GLSLShaderType::VERTEX );
	m_GlslProgram.compileShaderFromFile( "basic_basic.frag", GLSLShader::GLSLShaderType::FRAGMENT );

	// ���_���ƃV�F�[�_�̓��͕ϐ��}�b�s���O
	//m_GlslProgram.bindAttribLocation( 0, "VertexPosition" );
	//m_GlslProgram.bindAttribLocation( 1, "VertexColor");

    // ���_���
    m_Attribute.initialize();
    m_Attribute.addAttrib( m_TeaPot.getVetices(), m_TeaPot.getVerticesSize() * 3, 0 );
    float* color = new float[ m_TeaPot.getVerticesSize() * 3 ];
    for (int i = 0; i < m_TeaPot.getVerticesSize() * 3; i += 3)
    {
        color[ i ] = 1.f;
        color[ i+1 ] = 0.f;
        color[ i+2 ] = 0.f;
    }
    
    m_Attribute.addAttrib( color, m_TeaPot.getVerticesSize() * 3, 1 );
    delete[] color;
    m_Attribute.addIndice( m_TeaPot.getIndices(), m_TeaPot.getIndicesSize() * 3 );

	// �����N
	bool result =  m_GlslProgram.link();
	assert( result );

	// �V�F�[�_�[���g�p����
	m_GlslProgram.use();
}

//! �I��
void
GlFramework::finalize()
{
	// Model�֘A��j��
	ModelManager::getInstance()->removeModel( m_pCube[0] );
	ModelManager::getInstance()->removeModel( m_pCube[1] );
	delete m_pCube[0];
	delete m_pCube[1];
	m_pCube[0] = nullptr;
	m_pCube[1] = nullptr;
	ModelManager::deleteInstance();

	for( std::list< Camera* >::iterator it = m_CameraList.begin();
		it != m_CameraList.end();
		++it )
	{
		delete (*it);
	}
	m_CameraList.clear();
}

//! ���C�����[�v
void
GlFramework::mainLoop()
{
	glutMainLoop();
}

//! ��ʃT�C�Y�ύX���֐�
void
GlFramework::resize_( int w, int h )
{
	getInstance()->m_WindowSize = glm::vec2( w, h );

	// �`��͈�
	// ��������Ȃ̂Œ���
	switch( getInstance()->m_pViewport->getCoordType() )
	{
	case Viewport::eAbsolute:
		{
			const Viewport::ViewportInfo& info = getInstance()->m_pViewport->getViewport();
			glViewport((GLint)info.pos.x, (GLint)info.pos.y, (GLint)info.size.x, (GLint)info.size.y);
			printf("Viewport: Absolute, x: %.2f, y: %.2f, w: %.2f, h: %.2f\n", info.pos.x, info.pos.y, info.size.x, info.size.y );
		}
		break;
	case Viewport::eRelative:
		{
			const Viewport::ViewportInfo& info = getInstance()->m_pViewport->getViewport();
			glm::vec2 abs_pos = glm::vec2( 
				getInstance()->m_WindowSize.x * info.pos.x,
				getInstance()->m_WindowSize.y * info.pos.y
				);
			glm::vec2 abs_size = glm::vec2(
				getInstance()->m_WindowSize.x * info.size.x,
				getInstance()->m_WindowSize.y * info.size.y
				);
			glViewport( (GLint)abs_pos.x, (GLint)abs_pos.y, (GLint)abs_size.x, (GLint)abs_size.y );
			printf("Viewport: Relative, x: %.2f, y: %.2f, w: %.2f, h: %.2f\n", info.pos.x, info.pos.y, info.size.x, info.size.y );
	}
		break;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// fovy�͏c�̉�p
	// aspect�͉�/�c
	gluPerspective(30.0f, (double)w/(double)h, 1.0, 100.0);
	//glOrtho(-w/160.0f, w/160.0f, -h/120.0f, h/120.f, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
}

//! �`��
void
GlFramework::display_()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//glLoadIdentity();

	//ModelManager::getInstance()->draw();

    // uniform matrix�̓����_�[�֐��̒��炵��
    //glm::mat4 rotationMatrix = glm::rotate( mat4( 1.f ), glm::pi<float>() / 4.f , vec3( 0.f, 0.f, 1.f ) );
    //getInstance()->m_GlslProgram.setUniform( "RotationMatrix", rotationMatrix );
    getInstance()->m_GlslProgram.setUniform( "ProjectViewMtx", getInstance()->m_pCamera->getMatrix() );

    // �`��
    getInstance()->m_Attribute.draw();

	// �_�u���o�b�t�@�����O��L���ɂ���ɂ�2�ӏ��L�q���K�v
	// 1. glutInitDisplayMode��GLUT_DOUBLE���w��
	// 2. �X���b�v���������ӏ���glutSwapBuffers()���Ă�
	glutSwapBuffers();
}

//! �X�V
void
GlFramework::idle_()
{
    auto pos = getInstance()->m_pCamera->getPos();
    auto mat = glm::rotate( glm::mat4( 1.f ), glm::radians( 1.f ), glm::vec3( 0.f, 1.f, 0.f ) );
    auto pos2 = mat * glm::vec4( pos, 0.f );
    getInstance()->m_pCamera->setPos( pos2.x, pos2.y, pos2.z );
    getInstance()->m_pCamera->update();
	glutPostRedisplay();
}

//! �}�E�X����
void
GlFramework::mouse_( int button, int state, int x, int y )
{
	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		if(state == GLUT_DOWN)
		{
			glutIdleFunc(idle_);
		}
		else
		{
			glutIdleFunc(nullptr);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if(state == GLUT_DOWN)
		{
			glutPostRedisplay();
		}
		break;
	default:
		break;
	}
}

//! �L�[�{�[�h����
void
GlFramework::keyboard_( unsigned char key, int x, int y )
{
	switch(key)
	{
	case 'q':
	case 'Q':
	case '\033':
		exit(0);
		break;
	default:
		break;
	}
}
