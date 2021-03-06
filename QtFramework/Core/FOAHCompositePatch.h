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
            int texture_index;
            int material_index;
            int shadow_index;

            std::vector<PatchAttributes*>   neighbours;
            std::vector<Direction>         	connection_type;
            RowMatrix<GenericCurve3*>*		u_curves;
            RowMatrix<GenericCurve3*>*		v_curves;

            // ctor, copy ctor, assignment operator, dtor (they are required by the std::vector!)
            PatchAttributes();
            PatchAttributes(FirstOrderAlgebraicHyperbolicPatch&);
            PatchAttributes(const PatchAttributes&);
            PatchAttributes& operator =(const PatchAttributes&);
            ~PatchAttributes();

            GLboolean UpdateIsoparametricCurves(GLuint iso_line_count = 4);
            GLboolean UpdateImageAndVBO();

            GLvoid push(GLuint, PatchAttributes*);
            GLvoid pull(GLuint, PatchAttributes*);
        };

    protected:
        GLdouble                     _alpha;     // possible (shared) shape variables in directions u and v
        std::vector<PatchAttributes> _attributes;

        Matrix<DCoordinate3>         _big_control_net; // only in case of B-spline projects!
        bool enable_material = false;
    public:
        struct Pair{
            GLuint row_index, column_index;
        };
        struct PatchPoint {
            GLuint patch_index, row_index, column_index;
        };

        // special/default ctor
        FOAHCompositePatch3(GLdouble alpha, GLuint minimal_patch_count_to_be_reserved);

        // operations
        GLboolean InsertNewPatch();
        GLboolean DeleteExistingPatch(GLuint index);
        GLboolean ContinueExistingPatch(GLuint index, Direction direction);
        GLboolean JoinExistingPatches(GLuint index_0, Direction direction_0, GLuint index_1, Direction direction_1);
        GLboolean MergeExistingPatches(GLuint index_0, Direction direction_0, GLuint index_1, Direction direction_1);

        GLboolean RenderAllPatches(GLuint order, GLenum render_mode) const;
        GLboolean RenderSelectedPatch(GLuint index, GLuint order, GLenum render_mode) const;
        GLboolean RenderSelectedPatchWithoutData(GLuint index, GLuint order, GLenum render_mode) const;
        GLboolean RenderAllPatchData(GLenum render_mode) const;
        GLboolean RenderIsoparametricCurves(GLuint order, GLenum render_mode) const;


        // other setters and getters
        // ...

//        Adott ir??nyba visszaadja
        GLvoid pushPatch(GLuint index, GLuint direction);
        GLvoid pullPatch(GLuint index, GLuint direction);
        GLuint getPatchCount();
        DCoordinate3    getPoint(GLuint, GLuint, GLuint);
        GLvoid setPoint(GLuint patch_index, GLuint row, GLuint column, DCoordinate3 newPosition);

        Matrix<Pair> GetIndexesFromDirection(Direction direction, Direction other_direction);

        GLvoid setTexture(GLuint, int);
        GLvoid setMaterial(GLuint, int);
        GLvoid setShader(GLuint, int);
        GLvoid setEnableMaterial(bool);
        int getTexture(GLuint);
        int getMaterial(GLuint);
        int getShader(GLuint);
        // GLvoid setTextureArray(QOpenGLTexture**);

    private:
        GLvoid rotateMatrixRight(Matrix<Pair>*);
        GLvoid rotateMatrixLeft(Matrix<Pair>*);
        GLvoid setPoint(PatchAttributes* patch, GLuint row, GLuint column, DCoordinate3 newPosition);
        GLvoid setPointRecursively(GLuint patch_index, GLuint row, GLuint column, DCoordinate3 newPosition, std::vector<PatchPoint>& stack);
        GLvoid setPointRecursively(PatchAttributes* patch, GLuint row, GLuint column, DCoordinate3 newPosition, std::vector<PatchPoint>& stack);
        // used internally in Merge. otherwise the simple setPoint sets the corners too (but that version isn't correct if used in Merge and Join)
        GLvoid setPointWithoutCorner(GLuint patch_index, GLuint row, GLuint column, DCoordinate3 newPosition);
        GLvoid setPointRecursivelyWithoutCorner(GLuint patch_index, GLuint row, GLuint column, DCoordinate3 newPosition, std::vector<PatchPoint>& stack);
        GLvoid setPointRecursivelyWithoutCorner(PatchAttributes* patch, GLuint row, GLuint column, DCoordinate3 newPosition, std::vector<PatchPoint>& stack);
    };
}

#endif // FOAHCOMPOSITEPATCH3_H
