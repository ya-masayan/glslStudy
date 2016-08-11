#include "modelManager.h"

#include "model.h"
#include <assert.h>

ModelManager* ModelManager::m_pInstance = nullptr;

//! インスタンス生成
ModelManager*
ModelManager::createInstance()
{
	assert( !m_pInstance );
	m_pInstance = new ModelManager();
	return m_pInstance;
}

//! インスタンス破棄
void
ModelManager::deleteInstance()
{
	assert( m_pInstance );
	delete m_pInstance;
}
	
//! インスタンス取得
ModelManager*
ModelManager::getInstance()
{
	assert( m_pInstance );
	return m_pInstance;
}

//! Modelを追加
void
ModelManager::addModel( Model* model )
{
	m_ModelList.push_back( model );
}

//! Modelを除去
void
ModelManager::removeModel( Model* model )
{
	m_ModelList.remove( model );
}

#if 0
//! Modelを追加
void
ModelManager::getModel( Model* model )
{
	for( ModelList::iterator it = m_ModelList.begin();
		it != m_ModelList.end();
		++it )
	{
		if( model == *(it) )
		{
			return model;
		}
	}
}
#endif

//! Modelを描画
void
ModelManager::draw()
{
	for( ModelList::iterator it = m_ModelList.begin();
		it != m_ModelList.end();
		++it )
	{
		(*it)->draw();
	}
}
