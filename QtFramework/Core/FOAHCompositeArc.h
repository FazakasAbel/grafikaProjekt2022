#ifndef FOAHCOMPOSITEARC_H
#define FOAHCOMPOSITEARC_H

#include <Core/Colors4.h>
#include "FirstOrderAlgebraic-HyperbolicArc3.h"

namespace cagd
{
    class FOAHCompositeArc
    {
    public:
        enum Direction{LEFT, RIGHT};

        class ArcAttributes
        {
        public:
            FirstOrderAlgebraicHyperbolicArc3        *arc;
            GenericCurve3   *image;
            Color4          *color;           // use pointers to pre-defined colors, e.g., Color4 *color = &red;
            // other arc attributes
            // ...

            ArcAttributes   *previous, *next; // pointers to neighboring arc attributes
            Direction       previous_connection_type, next_connection_type;

            // ctor, copy ctor, assignment operator, dtor (they are required by the std::vector!)
            ArcAttributes();
            ArcAttributes(FirstOrderAlgebraicHyperbolicArc3&, Color4&);
            ArcAttributes(const ArcAttributes&);
            ArcAttributes& operator =(const ArcAttributes&);
            ~ArcAttributes();

            GLvoid push(GLuint, ArcAttributes*);
            GLvoid pull(GLuint, ArcAttributes*);
            GLvoid setPoint(GLuint, GLuint, GLdouble);
        };

    protected:
        GLdouble                   _alpha;               // possible (shared) shape parameter
        std::vector<ArcAttributes> _attributes;          // sequence of arc attributes

    public:
        // special/default ctor
        FOAHCompositeArc(GLdouble alpha = 1, GLuint minimal_arc_count_to_be_reserved = 5);
        ~FOAHCompositeArc();

        GLboolean InsertNewArc();
        GLboolean DeleteExistingArc(GLuint index);
        GLboolean ContinueExisitingArc(GLuint index, Direction direction);
        GLboolean JoinExistingArcs(GLuint index_0, Direction direction_0, GLuint index_1, Direction direction_1);
        GLboolean MergeExistingArcs(GLuint index_0, Direction direction_0, GLuint index_1, Direction direction_1);

        GLboolean RenderAllArcs(GLuint order, GLenum render_mode) const;
        GLboolean RenderSelectedArc(GLuint index, GLuint order, GLenum render_mode) const;
        GLboolean RenderAllArcData(GLenum render_mode) const;

        // other setters and getters
        // ...
        GLuint          getArcCount();
        // nth point of knt arc
        DCoordinate3    getPoint(GLuint, GLuint);
        GLvoid          setPoint(GLuint, GLuint, GLuint, GLdouble);
        GLvoid          pushArc(GLuint, GLuint);
        GLvoid          pullArc(GLuint, GLuint);
        ArcAttributes&  getPrevious(GLuint);
        ArcAttributes&  getNext(GLuint);
    };
}

#endif // FOAHCOMPOSITEARC_H
