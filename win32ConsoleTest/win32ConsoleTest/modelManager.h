#pragma once

#include <list>

class Model;

//! �V���O���g��
class ModelManager
{
public:
	//! �C���X�^���X����
	static ModelManager* createInstance();

	//! �C���X�^���X�j��
	static void deleteInstance();
	
	//! �C���X�^���X�擾
	static ModelManager* getInstance();

	//! Model��ǉ�
	void addModel( Model* model );

	//! Model������
	void removeModel( Model* model );

	//! Model���擾
	//void getModel( Model* model );

	//! Model��`��
	void draw();

private:
	//! �R���X�g���N�^
	ModelManager()
	{}

	//! �f�X�g���N�^
	~ModelManager()
	{}

private:
	typedef std::list< Model* > ModelList;

private:
	static ModelManager* m_pInstance;
	ModelList m_ModelList;
};
