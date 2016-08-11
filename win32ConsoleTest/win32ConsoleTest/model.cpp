#include "model.h"

//! ‰Šú‰»
void
Model::initialize( InitArg& arg )
{
	doInitialize_( arg );
}

//! I—¹
void
Model::finalize()
{
	doFinalize_();
}

//! •`‰æ
void
Model::draw()
{
	doDraw_();
}
