#ifndef FOAHCOMPOSITEPATCH3_H
#define FOAHCOMPOSITEPATCH3_H

#include <Core/Materials.h>
#include "./FirstOrderAlgebraic-HyperbolicPatch3.h"
#include "./TriangulatedMeshes3.h"
#include "./ShaderPrograms.h"
#include <QOpenGLTexture>

namespace cagd
{
    class FOAHCompositePatch3
    {
    public:
        enum Direction{N, NW, W, SW, S, SE, E, NE};

        class PatchAttributes
        {
        public:
            FirstOrderAlgebraicHyperbolicPatch          *patch;
            TriangulatedMesh3   *image;
            Material            *material; // use pointers to pre-defined materials
            QOpenGLTexture      *texture;  // use pointers to pre-defined textures
            ShaderProgram       *shader;   // use pointers to pre-defined shader programs

            // other attributes
            // ...

            PatchAttributes   *neighbours[8];
            Direction         connection_type[8];

            // ctor, copy ctor, assignment operator, dtor (they are required by the std::vector!)
        };

    protected:
        GLdouble                     _alpha[2];     // possible (shared) shape variables in directions u and v
        std::vector<PatchAttributes> _attributes;

        Matrix<DCoordinate3>         _big_control_net; // only in case of B-spline projects!
        struct Pair{
            GLuint row_index, column_index;
        };

    public:
        // special/default ctor
        FOAHCompositePatch3(/*GLdouble u_alpha = ..., GLdouble v_alpha = ..., GLuint minimial_patch_count_to_be_reserved = ...*/);

        // operations
        GLboolean InsertNewPatch();
        GLboolean DeleteExistingPatch(GLuint index);
        GLboolean ContinueExistingPatch(GLuint index, Direction direction);
        GLboolean JoinExistingPatches(GLuint index_0, Direction direction_0, GLuint index_1, Direction direction_1);
        GLboolean MergeExistingPatches(GLuint index_0, Direction direction_0, GLuint index_1, Direction direction_1);

        GLboolean RenderAllPatches(GLuint order, GLenum render_mode) const;
        GLboolean RenderSelectedPatch(GLuint index, GLuint order, GLenum render_mode) const;

        // other setters and getters
        // ...
        /*
        Adott irányba visszaadja
        */
        Matrix<Pair> GetIndexesFromDirection(Direction);
    };
}

#endif // FOAHCOMPOSITEPATCH3_H
