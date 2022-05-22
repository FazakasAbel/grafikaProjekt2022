#include "FirstOrderAlgebraic-HyperbolicPatch3.h"

using namespace cagd;

FirstOrderAlgebraicHyperbolicPatch::FirstOrderAlgebraicHyperbolicPatch(GLdouble alpha): TensorProductSurface3(0.0, alpha, 0.0, alpha, 4, 4)
{
    _alpha = alpha;
}

GLboolean FirstOrderAlgebraicHyperbolicPatch::UBlendingFunctionValues(GLdouble u_knot, RowMatrix<GLdouble> &blending_values) const
{
    if(u_knot < 0.0 || u_knot > alpha){
        return GL_FALSE;
    }

    blending_values.ResizeColumns(4);

    blending_values[0] = F0(u_knot);
    blending_values[1] = F1(u_knot);
    blending_values[2] = F2(u_knot);
    blending_values[3] = F3(u_knot);

    return GL_TRUE;
}


GLboolean FirstOrderAlgebraicHyperbolicPatch::SetAlpha(GLdouble alpha){
    if(alpha <= 0){
        return GL_FALSE;
    }

    _alpha = alpha;
    return GL_TRUE;
}

GLdouble FirstOrderAlgebraicHyperbolicPatch::GetAlpha() const{
    return _alpha;
}


GLboolean FirstOrderAlgebraicHyperbolicPatch::VBlendingFunctionValues(GLdouble v_knot, RowMatrix<GLdouble> &blending_values) const
{
    if(v_knot < 0.0 || v_knot > _alpha){
        return GL_FALSE;
    }

    blending_values.ResizeColumns(4);

    blending_values[0] = F0(v_knot);
    blending_values[1] = F1(v_knot);
    blending_values[2] = F2(v_knot);
    blending_values[3] = F3(v_knot);

    return GL_TRUE;
}

GLboolean FirstOrderAlgebraicHyperbolicPatch::CalculatePartialDerivatives(GLuint maximum_order_of_partial_derivatives, GLdouble u, GLdouble v, PartialDerivatives &pd) const
{
    if(u < 0.0 || u > _alpha || v < 0.0 || v > _alpha || maximum_order_of_partial_derivatives > 2)
        return GL_FALSE;

    RowMatrix<GLdouble> u_blending_values(4), d1_u_blending_values(4), d2_u_blending_values(4);

    u_blending_values[0] = F0(u);
    u_blending_values[1] = F1(u);
    u_blending_values[2] = F2(u);
    u_blending_values[3] = F3(u);

    d1_u_blending_values[0] = d1F0(u);
    d1_u_blending_values[1] = d1F1(u);
    d1_u_blending_values[2] = d1F2(u);
    d1_u_blending_values[3] = d1F3(u);

    d2_u_blending_values[0] = d2F0(u);
    d2_u_blending_values[1] = d2F1(u);
    d2_u_blending_values[2] = d2F2(u);
    d2_u_blending_values[3] = d2F3(u);

    RowMatrix<GLdouble> v_blending_values(4), d1_v_blending_values(4), d2_v_blending_values(4);

    v_blending_values[0] = F0(v);
    v_blending_values[1] = F1(v);
    v_blending_values[2] = F2(v);
    v_blending_values[3] = F3(v);

    d1_v_blending_values[0] = d1F0(v);
    d1_v_blending_values[1] = d1F1(v);
    d1_v_blending_values[2] = d1F2(v);
    d1_v_blending_values[3] = d1F3(v);

    d2_v_blending_values[0] = d2F0(v);
    d2_v_blending_values[1] = d2F1(v);
    d2_v_blending_values[2] = d2F2(v);
    d2_v_blending_values[3] = d2F3(v);

    pd.ResizeRows(maximum_order_of_partial_derivatives + 1);
    pd.LoadNullVectors();

    for(GLuint row = 0; row < 4; ++row){
        DCoordinate3 aux_d0_v, aux_d1_v, aux_d2_v;
        for(GLuint column = 0; column < 4; ++column)
        {
            aux_d0_v += _data(row, column) * v_blending_values(column);
            aux_d1_v += _data(row, column) * d1_v_blending_values(column);
            aux_d2_v += _data(row, column) * d2_v_blending_values(column);
        }
        pd(0, 0) += aux_d0_v * u_blending_values(row);
        pd(1, 0) += aux_d0_v * d1_u_blending_values(row);
        pd(1, 1) += aux_d1_v * u_blending_values(row);
        pd(2, 0) += aux_d0_v * d2_u_blending_values(row);
        pd(2, 1) += aux_d1_v * d1_u_blending_values(row);
        pd(2, 2) += aux_d2_v * u_blending_values(row);
    }

    return GL_TRUE;
}
