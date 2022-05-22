#include "../Core/FirstOrderAlgebraic-HyperbolicArc3.h"
#include "../Core/BasicFunctions.h"

FirstOrderAlgebraicHyperbolicArc3::FirstOrderAlgebraicHyperbolicArc3(GLdouble alpha) : LinearCombination3(0, alpha, 4, GL_STATIC_DRAW)
{
    _alpha = alpha;
}

GLboolean FirstOrderAlgebraicHyperbolicArc3::BlendingFunctionValues(GLdouble u, RowMatrix<GLdouble> &values) const{

    values.ResizeColumns(4);
    values[0] = F0(u);
    values[1] = F1(u);
    values[2] = F2(u);
    values[3] = F3(u);

    return GL_TRUE;
}

GLboolean FirstOrderAlgebraicHyperbolicArc3::CalculateDerivatives(GLuint max_order_of_derivatives, GLdouble u, Derivatives &d) const{

    if(max_order_of_derivatives > 2){
        return GL_FALSE;
    }

    d.ResizeRows(max_order_of_derivatives + 1);
    d.LoadNullVectors();

    if(max_order_of_derivatives >= 0){
        d[0] = F0(u) * _data[0] + F1(u) * _data[1] + F2(u) * _data[2] + F3(u) * _data[3];
    }

    if(max_order_of_derivatives >= 1){
        d[1] = d1F0(u) * _data[0] + d1F1(u) * _data[1] + d1F2(u) * _data[2] + d1F3(u) * _data[3];
    }

    if(max_order_of_derivatives >= 2){
        d[2] = d2F0(u) * _data[0] + d2F1(u) * _data[1] + d2F2(u) * _data[2] + d2F3(u) * _data[3];
    }

    return GL_TRUE;
}

GLboolean FirstOrderAlgebraicHyperbolicArc3::SetAlpha(GLdouble alpha){
    if(alpha <= 0){
        return GL_FALSE;
    }

    _alpha = alpha;
    return GL_TRUE;
}

GLdouble FirstOrderAlgebraicHyperbolicArc3::GetAlpha() const{
    return _alpha;
}
