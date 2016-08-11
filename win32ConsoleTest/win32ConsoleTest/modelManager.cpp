#include "modelManager.h"

#include "model.h"
#include <assert.h>

ModelManager* ModelManager::m_pInstance = nullptr;

//! �C���X�^���X����
ModelManager*
ModelManager::createInstance()
{
	assert( !m_pInstance );
	m_pInstance = new ModelManager();
	return m_pInstance;
}

//! �C���X�^���X�j��
void
ModelManager::deleteInstance()
{
	assert( m_pInstance );
	delete m_pInstance;
}
	
//! �C���X�^���X�擾
ModelManager*
ModelManager::getInstance()
{
	assert( m_pInstance );
	return m_pInstance;
}

//! Model��ǉ�
void
ModelManager::addModel( Model* model )
{
	m_ModelList.push_back( model );
}

//! Model������
void
ModelManager::removeModel( Model* model )
{
	m_ModelList.remove( model );
}

#if 0
//! Model��ǉ�
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

//! Model��`��
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
