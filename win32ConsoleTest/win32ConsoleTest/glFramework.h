#pragma once

#include "GLSLProgram.h"
#include "objLoader.h"
#include "attribImporter.h"
#include <list>

//! 前方宣言
class Camera;
class Viewport;
class ModelCube;

//! シングルトン
class GlFramework
{
public:
	struct InitArg
	{
		int argc;
		char** argv;
	};

public:
	//! インスタンスを生成
	static GlFramework* createInstance();

	//! インスタンスを破棄
	static void deleteInstance();

	//! インスタンスを取得
	static GlFramework* getInstance();

	//! 初期化
	void initialize( InitArg& arg );

	//! 終了
	void finalize();

	//! メインループ
	void mainLoop();

private:
	//! コンストラクタ
	GlFramework()
		: m_pViewport( nullptr )
		, m_WindowSize( 0.f, 0.f )
	{
		m_pCube[0] = nullptr;
		m_pCube[1] = nullptr;
	}

	//! デストラクタ
	~GlFramework()
	{}

	//! 画面サイズ変更時関数
	static void resize_( int w, int h );

	//! 描画
	static void display_();

	//! 更新
	static void idle_();

	//! マウス入力
	static void mouse_( int button, int state, int x, int y );

	//! キーボード入力
	static void keyboard_( unsigned char key, int x, int y );

private:
	static GlFramework*		m_pInstance;
	std::list< Camera* >	m_CameraList;
	Viewport*				m_pViewport; //!< 仮
	ModelCube*				m_pCube[2];	 //!< 仮
	masa::ObjLoader			m_TeaPot;
	masa::AttribImporter	m_Attribute;

	GLSLProgram				m_GlslProgram;
	glm::vec2				m_WindowSize;
    // とりあえず今はまだカメラは1つだけでいい
    Camera*                 m_pCamera;
};