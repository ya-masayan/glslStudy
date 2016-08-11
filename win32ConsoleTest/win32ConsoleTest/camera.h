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
	//! コンストラクタ
	Viewport()
		//: m_Pos( 0, 0 )
		//, m_Size( 0, 0 )
		: m_AdjustWindowSize( false )
	{}
	Viewport( const ViewportInfo& arg )
		: m_Info( arg )
		, m_AdjustWindowSize( false )
	{}

	//! デストラクタ
	~Viewport()
	{}

	//! ViewPortを設定
	void setViewport( const ViewportInfo& arg ){ m_Info = arg; }
	//! Viewportの情報を取得
	const ViewportInfo& getViewport(){ return m_Info; }

#if 0
	//! Windowサイズに合わせるか否かのフラグ
	void setAdjustWindowSize( bool enable ){ m_AdjustWindowSize = enable; }
	//! Windowサイズに合わせるか否かのフラグを取得
	bool getAdjustWindowSize(){ return m_AdjustWindowSize; }
#endif

	//! 座標指定の解釈の仕方を指定
	//! Absoluteの場合x, y, width, height は絶対座標を指定
	//! Relativeの場合x, y, width, height はWindowに対して位置割合を指定（0.f ～ 1.f）
	//! CoordTypeを設定した後は必ずsetViewportでパラメータを設定しなおしてください。
	void setCoordType( CoordType type ){ m_CoordType = type; }
	//! 座標指定の解釈の仕方を取得
	CoordType getCoordType(){ return m_CoordType; }

private:
	ViewportInfo m_Info;
	//glm::uvec2 m_Pos;
	//glm::uvec2 m_Size;	//!< xがwidth, yがheight

	bool m_AdjustWindowSize;	//!< ViewportをWindowサイズに合わせるかどうかのフラグ
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
	//! コンストラクタ
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

	//! デストラクタ
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

	//! 位置を設定
	void setPos( float x, float y, float z ){ setPos( glm::vec3( x, y, z ) ); }
	void setPos( const glm::vec3& pos ){ m_Eye = pos; }
	//! 位置を取得
	const glm::vec3& getPos(){ return m_Eye; }

	//! 向きを設定
	void setAt( float x, float y, float z ){ setAt( glm::vec3( x, y, z ) ); }
	void setAt( const glm::vec3& at ){ m_At = at; }
	//! 向きを取得
	const glm::vec3& getAt(){ return m_At; }

	//! 上方向を設定
	void setUp( float x, float y, float z ){ setUp( glm::vec3( x, y, z ) ); }
	void setUp( const glm::vec3& up ){ m_Up = up; }
	//! 上方向を取得
	const glm::vec3& getUp(){ return m_Up; }

	//! Viewportを追加。生成はユーザーが行って下さい
	//void addViewport( Viewport* viewport );
	Viewport* addViewport( const Viewport::ViewportInfo& arg );
    //! Viewportをセット
    void setViewport( Viewport* viewport ){ m_pViewPort = viewport; }
	//! Viewportを削除する
	void removeViewport( Viewport* viewport );

    //! perspectiveを設定
    void setPerspective( float fovy, float aspect, float near, float far )
    {
        m_Fovy   = fovy;
        m_Aspect = aspect;
        m_Near   = near;
        m_Far    = far;
    }

    //! 更新。ProjectView行列を算出
    void update();

    //! ProjectView行列取得
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
