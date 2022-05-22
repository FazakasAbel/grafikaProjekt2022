#ifndef FIRSTORDERALGEBRAICHYBERBOLICPATCH3_H
#define FIRSTORDERALGEBRAICHYBERBOLICPATCH3_H

#include "../Core/Matrices.h"
#include "../Core/RealSquareMatrices.h"
#include "../Core/TensorProductSurfaces3.h"
#include "../Core/BasicFunctions.h"

namespace cagd{
    class FirstOrderAlgebraicHyperbolicPatch: public TensorProductSurface3
    {
        private:
            GLdouble _alpha;

        public:
            FirstOrderAlgebraicHyperbolicPatch(GLdouble alpha = 1);

            GLboolean UBlendingFunctionValues(GLdouble u_knot, RowMatrix<GLdouble>& blending_values) const;

            GLboolean VBlendingFunctionValues(GLdouble v_knot, RowMatrix<GLdouble>& blending_values) const;

            GLboolean CalculatePartialDerivatives(
                    GLuint maximum_order_of_partial_derivatives,
                    GLdouble u, GLdouble v, PartialDerivatives& pd) const;

            GLboolean SetAlpha(GLdouble alpha);
            GLdouble GetAlpha() const;

    };
}


#endif // FIRSTORDERALGEBRAICHYBERBOLICPATCH3_H
