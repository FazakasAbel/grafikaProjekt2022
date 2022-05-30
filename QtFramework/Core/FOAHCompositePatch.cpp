#include "../Core/FOAHCompositePatch.h"

using namespace std;
using namespace cagd;

FOAHCompositePatch3::PatchAttributes::PatchAttributes() : patch(nullptr), image(nullptr), neighbours(8, nullptr)
{
}

FOAHCompositePatch3::PatchAttributes::PatchAttributes(FirstOrderAlgebraicHyperbolicPatch& patch)
{
    this->patch = new FirstOrderAlgebraicHyperbolicPatch(patch);
    image = this->patch->GenerateImage(200, 200);
    this->neighbours.resize(8);
    this->connection_type.resize(8);
    for (auto& neighbor : this->neighbours)
        neighbor = nullptr;
}

FOAHCompositePatch3::PatchAttributes::PatchAttributes(const PatchAttributes& patchAttributes) : neighbours(patchAttributes.neighbours)
{
    this->patch = new FirstOrderAlgebraicHyperbolicPatch(*patchAttributes.patch);
    this->image = new TriangulatedMesh3(*patchAttributes.image);
    for (GLuint i = 0; i < 8; i++)
        connection_type[i] = patchAttributes.connection_type[i];
}

FOAHCompositePatch3::PatchAttributes& FOAHCompositePatch3::PatchAttributes::operator =(const PatchAttributes& rhs)
{
    if (&rhs == this)
        return *this;

    if (rhs.patch)
        this->patch = new FirstOrderAlgebraicHyperbolicPatch(*rhs.patch);

    if (rhs.image)
        this->image = new TriangulatedMesh3(*rhs.image);

    for (GLuint i = 0; i < 8; i++)
    {
        this->connection_type[i] = rhs.connection_type[i];
        this->neighbours[i] = rhs.neighbours[i];
    }

    return *this;
}

FOAHCompositePatch3::PatchAttributes::~PatchAttributes()
{
    if (patch)
    {
        delete patch;
        patch = nullptr;
    }
    if (image)
    {
        delete image;
        image = nullptr;
    }
}

FOAHCompositePatch3::FOAHCompositePatch3(GLdouble alpha, GLuint minimal_patch_count_to_be_reserved) : _alpha(alpha)
{
    _attributes.reserve(minimal_patch_count_to_be_reserved);
}

GLboolean FOAHCompositePatch3::InsertNewPatch()
{
    try
    {
        size_t patch_count = _attributes.size();
        _attributes.resize(patch_count + 1);
        _attributes[patch_count].patch = new FirstOrderAlgebraicHyperbolicPatch();

        FirstOrderAlgebraicHyperbolicPatch &newPatch = *_attributes[patch_count].patch;
        newPatch(0,0) = DCoordinate3(0,0,0);
        newPatch(0,1) = DCoordinate3(0,0,1);
        newPatch(0,2) = DCoordinate3(0,0,2);
        newPatch(0,3) = DCoordinate3(0,0,3);

        newPatch(1,0) = DCoordinate3(1,0,0);
        newPatch(1,1) = DCoordinate3(1,0,1);
        newPatch(1,2) = DCoordinate3(1,0,2);
        newPatch(1,3) = DCoordinate3(1,0,3);

        newPatch(2,0) = DCoordinate3(2,0,0);
        newPatch(2,1) = DCoordinate3(2,0,1);
        newPatch(2,2) = DCoordinate3(2,0,2);
        newPatch(2,3) = DCoordinate3(2,0,3);

        newPatch(3,0) = DCoordinate3(3,0,0);
        newPatch(3,1) = DCoordinate3(3,0,1);
        newPatch(3,2) = DCoordinate3(3,0,2);
        newPatch(3,3) = DCoordinate3(3,0,3);

        newPatch.UpdateVertexBufferObjectsOfData();
        _attributes[patch_count].image = newPatch.GenerateImage(2, 200);
        TriangulatedMesh3 &image = *_attributes[patch_count].image;
        image.UpdateVertexBufferObjects();

        return GL_TRUE;
    }
    catch (Exception e)
    {
        cout << "InsertNewPatch error!" << endl;
        return GL_FALSE;
    }
}

GLboolean FOAHCompositePatch3::RenderAllPatches(GLuint order, GLenum render_mode) const
{
    for (auto& patchAttr : _attributes)
    {
        if (patchAttr.image)
            patchAttr.image->Render(render_mode);
        else
            return GL_FALSE;
    }

    return GL_TRUE;
}

GLboolean FOAHCompositePatch3::RenderSelectedPatch(GLuint index, GLuint order, GLenum render_mode) const
{
    if (_attributes[index].image)
    {
        _attributes[index].image->Render(render_mode);
        _attributes[index].patch->RenderData(render_mode);
    }
    else
        return GL_FALSE;

    return GL_FALSE;
}

GLboolean FOAHCompositePatch3::RenderAllPatchData(GLenum render_mode) const
{
    for (auto& patchAttr : _attributes)
        patchAttr.patch->RenderData(render_mode);

    return GL_TRUE;
}

GLboolean FOAHCompositePatch3::ContinueExistingPatch(GLuint index, Direction direction){

}
