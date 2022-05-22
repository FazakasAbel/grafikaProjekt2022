#ifndef BASICFUNCTIONS_H
#define BASICFUNCTIONS_H

#include <GL/glew.h>
#include <cmath>

namespace cagd
{
    //alfa > 0
    extern GLdouble alpha;

    GLdouble F0(GLdouble u);
    GLdouble F1(GLdouble u);
    GLdouble F2(GLdouble u);
    GLdouble F3(GLdouble u);

    GLdouble d1F0(GLdouble u);
    GLdouble d1F1(GLdouble u);
    GLdouble d1F2(GLdouble u);
    GLdouble d1F3(GLdouble u);

    GLdouble d2F0(GLdouble u);
    GLdouble d2F1(GLdouble u);
    GLdouble d2F2(GLdouble u);
    GLdouble d2F3(GLdouble u);
}

#endif // BASICFUNCTIONS_H
