#pragma once

#include "model.h"

class ModelCube : public Model
{
public:
	const float* getVertexData();
	int		     getVertexSize();
	const float* getColorData();
	int	         getColorSize();

protected:
	virtual void doInitialize_( InitArg& arg ) override;
	virtual void doFinalize_() override;
	virtual void doDraw_() override;
};
