#ifndef FIRSTORDERALGEBRAICHYPERBOLICARC3_H
#define FIRSTORDERALGEBRAICHYPERBOLICARC3_H
#include "LinearCombination3.h"

using namespace cagd;

class FirstOrderAlgebraicHyperbolicArc3: public LinearCombination3
{
protected:

    GLdouble _alpha;

public:

    FirstOrderAlgebraicHyperbolicArc3(GLdouble alpha = 1);
    FirstOrderAlgebraicHyperbolicArc3(const FirstOrderAlgebraicHyperbolicArc3& arc);

    GLboolean BlendingFunctionValues(GLdouble u, RowMatrix<GLdouble> &values) const;

    GLboolean CalculateDerivatives(
            GLuint max_order_of_derivatives, GLdouble u, Derivatives &d) const;

    GLboolean SetAlpha(GLdouble alpha);
    GLdouble GetAlpha() const;

};

#endif // FIRSTORDERALGEBRAICHYPERBOLICARC3_H
