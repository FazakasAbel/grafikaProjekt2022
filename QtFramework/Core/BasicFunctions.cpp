#include "BasicFunctions.h"

namespace cagd
{
    GLdouble alpha = 1;

    GLdouble F0(GLdouble u){
        return F3(alpha - u);
    }
    GLdouble F1(GLdouble u){
        return F2(alpha - u);
    }
    GLdouble F2(GLdouble u){
        return (alpha - u  + sinh(alpha - u) + sinh(u) - sinh(alpha) + u * cosh(alpha) - alpha * cosh(u)) * sinh(alpha) / (alpha - sinh(alpha)) / (2 * sinh(alpha) - alpha - alpha  * cosh(alpha));
    }
    GLdouble F3(GLdouble u){
        return (u - sinh(u)) / (alpha - sinh(alpha));
    }

    GLdouble d1F0(GLdouble u){
        return -d1F3(alpha - u);
    }
    GLdouble d1F1(GLdouble u){
        return -d1F2(alpha - u);
    }
    GLdouble d1F2(GLdouble u){
        return (sinh(alpha)*(-cosh(u-alpha)-alpha*sinh(u)+cosh(u)+cosh(alpha)-1))/((alpha-sinh(alpha))*(2*sinh(alpha)-alpha*cosh(alpha)-alpha));
    }
    GLdouble d1F3(GLdouble u){
        return (cosh(u)-1)/(sinh(alpha)-alpha);
    }

    GLdouble d2F0(GLdouble u){
        return d2F3(alpha - u);
    }
    GLdouble d2F1(GLdouble u){
        return d2F2(alpha - u);
    }
    GLdouble d2F2(GLdouble u){
        return (sinh(alpha)*(sinh(u-alpha)-sinh(u)+alpha*cosh(u)))/((sinh(alpha)-alpha)*(2*sinh(alpha)-alpha*cosh(alpha)-alpha));
    }
    GLdouble d2F3(GLdouble u){
        return sinh(u)/(sinh(alpha)-alpha);
    }

}
