#pragma once

#include "model.h"

class ModelTriangle : public Model
{
public:
    static const float* getVertexData();
    static int          getVertexSize();
    static const float* getColorData();
    static int          getColorSize();

protected:
	virtual void doInitialize_( InitArg& arg ) override;
	virtual void doFinalize_() override;
	virtual void doDraw_() override;
};

class ModelSquare : public Model
{
public:
    static const float* getVertexData();
    static int          getVertexSize();
    static const float* getColorData();
    static int          getColorSize();
    static const int*   getIndice();
    static int          getIndiceSize();

protected:
    virtual void doInitialize_( InitArg& arg ) override{}
    virtual void doFinalize_() override{}
    virtual void doDraw_() override{}
};