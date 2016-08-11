#include "modelCube.h"

#include <GL/glew.h>
#define GLEW_STATIC
#include <GL/glut.h>

namespace
{
//! ���_�f�[�^
const float vertex[][3] = {
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
float color[][3] = {
	{ 1.0, 0.0, 0.0 }, /* �� */
	{ 0.0, 1.0, 0.0 }, /* �� */
	{ 0.0, 0.0, 1.0 }, /* �� */
	{ 1.0, 1.0, 0.0 }, /* �� */
	{ 1.0, 0.0, 1.0 }, /* �}�[���^ */
	{ 0.0, 1.0, 1.0 }  /* �V�A�� �@*/
};

}

const float*
ModelCube::getVertexData()
{
	return &( vertex[0][0] );
}

int
ModelCube::getVertexSize()
{
    return sizeof( vertex ) / sizeof( vertex[ 0 ][ 0 ] ) * sizeof( float );
}

const float*
ModelCube::getColorData()
{
    return &(color[ 0 ][ 0 ]);
}

int
ModelCube::getColorSize()
{
    return sizeof( color ) / sizeof( color[ 0 ][ 0 ] ) * sizeof( float );
}

void
ModelCube::doInitialize_( InitArg& /*arg*/ )
{}

void
ModelCube::doFinalize_()
{}

void
ModelCube::doDraw_()
{
	glPushMatrix();
	// SRT�s��ݒ�
	static double r = 0.0;
	++r;
	r = r >= 360.0 ? 0.0 : r;
	glTranslated( getPos().x, getPos().y, getPos().z );
	glRotated( r/*getRotate().w*/, getRotate().x, getRotate().y, getRotate().z );
	glScaled( getScale().x, getScale().y, getScale().z );

	// �`��
	glBegin(GL_QUADS);
	{
		for(int i=0; i<6; ++i)
		{
			glColor3fv(color[i]);
			for(int j=0; j<4; ++j)
			{
				glVertex3fv(vertex[face[i][j]]);
			}
		}
	}
	glEnd();
	glPopMatrix();
}