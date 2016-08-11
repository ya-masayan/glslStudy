#pragma once

#include <list>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class  Viewport
{
public:
	struct ViewportInfo
	{
		ViewportInfo& operator =( const ViewportInfo& info )
		{
			pos = info.pos;
			size = info.size;
			return *this;
		}

		ViewportInfo()
			: pos( 0, 0 )
			, size( 0, 0 )
		{}

		glm::vec2 pos;
		glm::vec2 size;
	};

	enum CoordType
	{
		eAbsolute,
		eRelative,

		eCoordTypeMax
	};

public:
	//! �R���X�g���N�^
	Viewport()
		//: m_Pos( 0, 0 )
		//, m_Size( 0, 0 )
		: m_AdjustWindowSize( false )
	{}
	Viewport( const ViewportInfo& arg )
		: m_Info( arg )
		, m_AdjustWindowSize( false )
	{}

	//! �f�X�g���N�^
	~Viewport()
	{}

	//! ViewPort��ݒ�
	void setViewport( const ViewportInfo& arg ){ m_Info = arg; }
	//! Viewport�̏����擾
	const ViewportInfo& getViewport(){ return m_Info; }

#if 0
	//! Window�T�C�Y�ɍ��킹�邩�ۂ��̃t���O
	void setAdjustWindowSize( bool enable ){ m_AdjustWindowSize = enable; }
	//! Window�T�C�Y�ɍ��킹�邩�ۂ��̃t���O���擾
	bool getAdjustWindowSize(){ return m_AdjustWindowSize; }
#endif

	//! ���W�w��̉��߂̎d�����w��
	//! Absolute�̏ꍇx, y, width, height �͐�΍��W���w��
	//! Relative�̏ꍇx, y, width, height ��Window�ɑ΂��Ĉʒu�������w��i0.f �` 1.f�j
	//! CoordType��ݒ肵����͕K��setViewport�Ńp�����[�^��ݒ肵�Ȃ����Ă��������B
	void setCoordType( CoordType type ){ m_CoordType = type; }
	//! ���W�w��̉��߂̎d�����擾
	CoordType getCoordType(){ return m_CoordType; }

private:
	ViewportInfo m_Info;
	//glm::uvec2 m_Pos;
	//glm::uvec2 m_Size;	//!< x��width, y��height

	bool m_AdjustWindowSize;	//!< Viewport��Window�T�C�Y�ɍ��킹�邩�ǂ����̃t���O
	CoordType m_CoordType;
};

class Camera
{
public:
	struct InitArg
	{
		InitArg()
			: eye( 0.f, 0.f, 0.f )
			, at( 0.f, 0.f, 1.f )
			, up( 0.f, 1.f, 0.f )
			//, viewport( nullptr )
		{}

		glm::vec3 eye;
		glm::vec3 at;
		glm::vec3 up;
		//Viewport* viewport;
	};

public:
	//! �R���X�g���N�^
    Camera( const InitArg& arg )
        : m_Eye( arg.eye )
        , m_At( arg.at )
        , m_Up( arg.up )
        , m_pViewPort( nullptr )
        , m_Fovy( glm::radians( 45.f ) )
        , m_Aspect( 4.f / 3.f )
        , m_Near( 0.1f )
        , m_Far( 100.f )
    {}

	//! �f�X�g���N�^
	~Camera()
	{
		for( std::list< Viewport* >::iterator it = m_ViewportList.begin();
			it != m_ViewportList.end();
			++it )
		{
			delete (*it);
		}
		m_ViewportList.clear();
	}

	//! �ʒu��ݒ�
	void setPos( float x, float y, float z ){ setPos( glm::vec3( x, y, z ) ); }
	void setPos( const glm::vec3& pos ){ m_Eye = pos; }
	//! �ʒu���擾
	const glm::vec3& getPos(){ return m_Eye; }

	//! ������ݒ�
	void setAt( float x, float y, float z ){ setAt( glm::vec3( x, y, z ) ); }
	void setAt( const glm::vec3& at ){ m_At = at; }
	//! �������擾
	const glm::vec3& getAt(){ return m_At; }

	//! �������ݒ�
	void setUp( float x, float y, float z ){ setUp( glm::vec3( x, y, z ) ); }
	void setUp( const glm::vec3& up ){ m_Up = up; }
	//! ��������擾
	const glm::vec3& getUp(){ return m_Up; }

	//! Viewport��ǉ��B�����̓��[�U�[���s���ĉ�����
	//void addViewport( Viewport* viewport );
	Viewport* addViewport( const Viewport::ViewportInfo& arg );
    //! Viewport���Z�b�g
    void setViewport( Viewport* viewport ){ m_pViewPort = viewport; }
	//! Viewport���폜����
	void removeViewport( Viewport* viewport );

    //! perspective��ݒ�
    void setPerspective( float fovy, float aspect, float near, float far )
    {
        m_Fovy   = fovy;
        m_Aspect = aspect;
        m_Near   = near;
        m_Far    = far;
    }

    //! �X�V�BProjectView�s����Z�o
    void update();

    //! ProjectView�s��擾
    const glm::mat4& getMatrix(){ return m_ProjViewMtx; }

private:
	static const int c_ViewportMax = 100;

private:
	glm::vec3 m_Eye;
	glm::vec3 m_At;
	glm::vec3 m_Up;
	std::list< Viewport* > m_ViewportList;
    Viewport*   m_pViewPort;
    glm::mat4   m_ProjViewMtx;
    float       m_Fovy;
    float       m_Aspect;
    float       m_Near;
    float       m_Far;
};
