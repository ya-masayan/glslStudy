#include "model.h"

//! ������
void
Model::initialize( InitArg& arg )
{
	doInitialize_( arg );
}

//! �I��
void
Model::finalize()
{
	doFinalize_();
}

//! �`��
void
Model::draw()
{
	doDraw_();
}
