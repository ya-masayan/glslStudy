#pragma once

#include <list>

class Model;

//! シングルトン
class ModelManager
{
public:
	//! インスタンス生成
	static ModelManager* createInstance();

	//! インスタンス破棄
	static void deleteInstance();
	
	//! インスタンス取得
	static ModelManager* getInstance();

	//! Modelを追加
	void addModel( Model* model );

	//! Modelを除去
	void removeModel( Model* model );

	//! Modelを取得
	//void getModel( Model* model );

	//! Modelを描画
	void draw();

private:
	//! コンストラクタ
	ModelManager()
	{}

	//! デストラクタ
	~ModelManager()
	{}

private:
	typedef std::list< Model* > ModelList;

private:
	static ModelManager* m_pInstance;
	ModelList m_ModelList;
};
