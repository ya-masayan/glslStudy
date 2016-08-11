#include "modelPrimitive.h"

#include <GL/glew.h>
#define GLEW_STATIC
#include <GL/glut.h>

namespace {

float triangleVertex[] =
{
    -0.8f, -0.8f, 0.0f,
     0.8f, -0.8f, 0.0f,
     0.0f,  0.8f, 0.0f
};

float triangleColor[] =
{
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};


float squareVertex[] =
{
    -0.8f, -0.8f, 0.0f,
     0.8f, -0.8f, 0.0f,
     0.8f,  0.8f, 0.0f,
    -0.8f,  0.8f, 0.0f
};

float squareColor[] =
{
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    0.5f, 0.0f, 0.5f
};

int squareIndice[] =
{
    0, 1, 2,
    2, 3, 0
};


}


const float*
ModelTriangle::getVertexData()
{
    return &(triangleVertex[ 0 ]);
}

int
ModelTriangle::getVertexSize()
{
    return sizeof( triangleVertex ) / sizeof( triangleVertex[ 0 ] );
}

const float*
ModelTriangle::getColorData()
{
    return &(triangleColor[ 0 ]);
}

int
ModelTriangle::getColorSize()
{
    return sizeof( triangleColor ) / sizeof( triangleColor[ 0 ] );
}

void
ModelTriangle::doInitialize_( InitArg& /*arg*/ )
{}

void
ModelTriangle::doFinalize_()
{}

void
ModelTriangle::doDraw_()
{
}


const float*
ModelSquare::getVertexData()
{
    return &(squareVertex[ 0 ]);
}

int
ModelSquare::getVertexSize()
{
    return sizeof( squareVertex ) / sizeof( squareVertex[ 0 ] );
}

const float*
ModelSquare::getColorData()
{
    return &(squareColor[ 0 ]);
}

int
ModelSquare::getColorSize()
{
    return sizeof( squareColor ) / sizeof( squareColor[ 0 ] );
}

const int*
ModelSquare::getIndice()
{
    return squareIndice;
}

int
ModelSquare::getIndiceSize()
{
    return sizeof( squareIndice ) / sizeof( squareIndice[ 0 ] );
}
