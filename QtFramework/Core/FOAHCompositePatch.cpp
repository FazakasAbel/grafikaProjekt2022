#include "../Core/FOAHCompositePatch.h"

using namespace std;
using namespace cagd;

FOAHCompositePatch3::PatchAttributes::PatchAttributes() : patch(nullptr), image(nullptr), neighbours(8, nullptr), connection_type(8, N)
{
}

FOAHCompositePatch3::PatchAttributes::PatchAttributes(FirstOrderAlgebraicHyperbolicPatch& patch)
{
    this->patch = new FirstOrderAlgebraicHyperbolicPatch(patch);
    image = this->patch->GenerateImage(30, 30);
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

GLboolean FOAHCompositePatch3::PatchAttributes::UpdateIsoparametricCurves(GLuint iso_line_count)
{
    u_curves = patch->GenerateUIsoparametricLines(iso_line_count, 2, 200);
    v_curves = patch->GenerateVIsoparametricLines(iso_line_count, 2, 200);
    for (GLuint i = 0; i < iso_line_count; i++)
    {
        if (!(*u_curves)[i]->UpdateVertexBufferObjects(1))
            return GL_FALSE;
        if (!(*v_curves)[i]->UpdateVertexBufferObjects(1))
            return GL_FALSE;
    }

    return GL_TRUE;
}

GLboolean FOAHCompositePatch3::PatchAttributes::UpdateImageAndVBO()
{
    if (!patch->UpdateVertexBufferObjectsOfData())
    {
        std::cout << "Error updating VBO of patch data!" << std::endl;
        return GL_FALSE;
    }

    image = patch->GenerateImage(30, 30);
    if (!image || !image->UpdateVertexBufferObjects())
    {
        std::cout << "Error updating VBO of patch image!" << std::endl;
        return GL_FALSE;
    }

    if (!UpdateIsoparametricCurves())
    {
        std::cout << "Error updating isoparametric curves of patch!" << std::endl;
        return GL_FALSE;
    }

    return GL_TRUE;
}

GLvoid FOAHCompositePatch3::PatchAttributes::push(GLuint axis, PatchAttributes* prev)
{
    for (GLuint i = 0; i < 4; i++)
        for (GLuint j = 0; j < 4; j++)
            (*patch)(i,j)[axis] += 1;

    UpdateImageAndVBO();
}

GLvoid FOAHCompositePatch3::PatchAttributes::pull(GLuint axis, PatchAttributes* prev)
{
    for (GLuint i = 0; i < 4; i++)
        for (GLuint j = 0; j < 4; j++)
            (*patch)(i,j)[axis] -= 1;

   UpdateImageAndVBO();
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
        newPatch(1,1) = DCoordinate3(1,2,1);
        newPatch(1,2) = DCoordinate3(1,2,2);
        newPatch(1,3) = DCoordinate3(1,0,3);

        newPatch(2,0) = DCoordinate3(2,0,0);
        newPatch(2,1) = DCoordinate3(2,2,1);
        newPatch(2,2) = DCoordinate3(2,2,2);
        newPatch(2,3) = DCoordinate3(2,0,3);

        newPatch(3,0) = DCoordinate3(3,0,0);
        newPatch(3,1) = DCoordinate3(3,0,1);
        newPatch(3,2) = DCoordinate3(3,0,2);
        newPatch(3,3) = DCoordinate3(3,0,3);

        return _attributes[patch_count].UpdateImageAndVBO();
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

GLboolean FOAHCompositePatch3::RenderIsoparametricCurves(GLuint order, GLenum render_mode) const
{
    for (auto& patchAttr : _attributes)
    {
        for (GLuint i = 0; i < patchAttr.u_curves->GetColumnCount(); i++)
        {
            if (!(*patchAttr.u_curves)[i] || !(*patchAttr.v_curves)[i])
                return GL_FALSE;

            (*patchAttr.u_curves)[i]->RenderDerivatives(order, render_mode);
            (*patchAttr.v_curves)[i]->RenderDerivatives(order, render_mode);
        }
    }
    return GL_TRUE;
}

GLboolean FOAHCompositePatch3::ContinueExistingPatch(GLuint index, Direction direction){
    if(direction == NW || direction == SW || direction == SE || direction == NE){
        return GL_FALSE;
    }

    if(index >= _attributes.size()){
        std::cout << "Patch index invalid!" << std::endl;
        return GL_FALSE;
    }

    PatchAttributes* attribute = &_attributes[index];
    if (attribute->neighbours[direction])
    {
        std::cout << "Patch already has a neighbor in given direction!";
        return GL_FALSE;
    }

    size_t patch_count = _attributes.size();
    _attributes.resize(patch_count + 1);
    _attributes[patch_count].patch = new FirstOrderAlgebraicHyperbolicPatch();

    FirstOrderAlgebraicHyperbolicPatch &patch = *_attributes[patch_count].patch;

    switch(direction){

        case (N):
        {
            patch.SetData(3, 0, (*attribute->patch)(0, 0));
            patch.SetData(3, 1, (*attribute->patch)(0, 1));
            patch.SetData(3, 2, (*attribute->patch)(0, 2));
            patch.SetData(3, 3, (*attribute->patch)(0, 3));

            DCoordinate3 delta0 = (*attribute->patch)(0, 0) - (*attribute->patch)(1, 0);
            DCoordinate3 delta1 = (*attribute->patch)(0, 1) - (*attribute->patch)(1, 1);
            DCoordinate3 delta2 = (*attribute->patch)(0, 2) - (*attribute->patch)(1, 2);
            DCoordinate3 delta3 = (*attribute->patch)(0, 3) - (*attribute->patch)(1, 3);

            patch.SetData(2, 0, (*attribute->patch)(0, 0) + delta0);
            patch.SetData(2, 1, (*attribute->patch)(0, 1) + delta1);
            patch.SetData(2, 2, (*attribute->patch)(0, 2) + delta2);
            patch.SetData(2, 3, (*attribute->patch)(0, 3) + delta3);

            patch.SetData(1, 0, (*attribute->patch)(0, 0) + 2 * delta0);
            patch.SetData(1, 1, (*attribute->patch)(0, 1) + 2 * delta1);
            patch.SetData(1, 2, (*attribute->patch)(0, 2) + 2 * delta2);
            patch.SetData(1, 3, (*attribute->patch)(0, 3) + 2 * delta3);

            patch.SetData(0, 0, (*attribute->patch)(0, 0) + 3 * delta0);
            patch.SetData(0, 1, (*attribute->patch)(0, 1) + 3 * delta1);
            patch.SetData(0, 2, (*attribute->patch)(0, 2) + 3 * delta2);
            patch.SetData(0, 3, (*attribute->patch)(0, 3) + 3 * delta3);

            _attributes[index].connection_type[direction] = S;
            _attributes[patch_count].neighbours[S] = &_attributes[index];
            _attributes[patch_count].connection_type[S] = direction;
        }
        break;
        case (W):
        {
            patch.SetData(0, 3, (*attribute->patch)(0, 0));
            patch.SetData(1, 3, (*attribute->patch)(1, 0));
            patch.SetData(2, 3, (*attribute->patch)(2, 0));
            patch.SetData(3, 3, (*attribute->patch)(3, 0));

            DCoordinate3 delta0 = (*attribute->patch)(0, 0) - (*attribute->patch)(0, 1);
            DCoordinate3 delta1 = (*attribute->patch)(1, 0) - (*attribute->patch)(1, 1);
            DCoordinate3 delta2 = (*attribute->patch)(2, 0) - (*attribute->patch)(2, 1);
            DCoordinate3 delta3 = (*attribute->patch)(3, 0) - (*attribute->patch)(3, 1);

            patch.SetData(0, 2, (*attribute->patch)(0, 0) + delta0);
            patch.SetData(1, 2, (*attribute->patch)(1, 0) + delta1);
            patch.SetData(2, 2, (*attribute->patch)(2, 0) + delta2);
            patch.SetData(3, 2, (*attribute->patch)(3, 0) + delta3);

            patch.SetData(0, 1, (*attribute->patch)(0, 0) + 2 * delta0);
            patch.SetData(1, 1, (*attribute->patch)(1, 0) + 2 * delta1);
            patch.SetData(2, 1, (*attribute->patch)(2, 0) + 2 * delta2);
            patch.SetData(3, 1, (*attribute->patch)(3, 0) + 2 * delta3);

            patch.SetData(0, 0, (*attribute->patch)(0, 0) + 3 * delta0);
            patch.SetData(1, 0, (*attribute->patch)(1, 0) + 3 * delta1);
            patch.SetData(2, 0, (*attribute->patch)(2, 0) + 3 * delta2);
            patch.SetData(3, 0, (*attribute->patch)(3, 0) + 3 * delta3);

            _attributes[index].connection_type[direction] = E;
            _attributes[patch_count].neighbours[E] = &_attributes[index];
            _attributes[patch_count].connection_type[E] = direction;
        }
        break;
        case (E):
        {
            patch.SetData(0, 0, (*attribute->patch)(0, 3));
            patch.SetData(1, 0, (*attribute->patch)(1, 3));
            patch.SetData(2, 0, (*attribute->patch)(2, 3));
            patch.SetData(3, 0, (*attribute->patch)(3, 3));

            DCoordinate3 delta0 = (*attribute->patch)(0, 3) - (*attribute->patch)(0, 2);
            DCoordinate3 delta1 = (*attribute->patch)(1, 3) - (*attribute->patch)(1, 2);
            DCoordinate3 delta2 = (*attribute->patch)(2, 3) - (*attribute->patch)(2, 2);
            DCoordinate3 delta3 = (*attribute->patch)(3, 3) - (*attribute->patch)(3, 2);

            patch.SetData(0, 1, (*attribute->patch)(0, 3) + delta0);
            patch.SetData(1, 1, (*attribute->patch)(1, 3) + delta1);
            patch.SetData(2, 1, (*attribute->patch)(2, 3) + delta2);
            patch.SetData(3, 1, (*attribute->patch)(3, 3) + delta3);

            patch.SetData(0, 2, (*attribute->patch)(0, 3) + 2 * delta0);
            patch.SetData(1, 2, (*attribute->patch)(1, 3) + 2 * delta1);
            patch.SetData(2, 2, (*attribute->patch)(2, 3) + 2 * delta2);
            patch.SetData(3, 2, (*attribute->patch)(3, 3) + 2 * delta3);

            patch.SetData(0, 3, (*attribute->patch)(0, 3) + 3 * delta0);
            patch.SetData(1, 3, (*attribute->patch)(1, 3) + 3 * delta1);
            patch.SetData(2, 3, (*attribute->patch)(2, 3) + 3 * delta2);
            patch.SetData(3, 3, (*attribute->patch)(3, 3) + 3 * delta3);

            _attributes[index].connection_type[direction] = W;
            _attributes[patch_count].neighbours[W] = &_attributes[index];
            _attributes[patch_count].connection_type[W] = direction;
        }
        break;
        case (S):
        {
            patch.SetData(0, 0, (*attribute->patch)(3, 0));
            patch.SetData(0, 1, (*attribute->patch)(3, 1));
            patch.SetData(0, 2, (*attribute->patch)(3, 2));
            patch.SetData(0, 3, (*attribute->patch)(3, 3));

            DCoordinate3 delta0 = (*attribute->patch)(3, 0) - (*attribute->patch)(2, 0);
            DCoordinate3 delta1 = (*attribute->patch)(3, 1) - (*attribute->patch)(2, 1);
            DCoordinate3 delta2 = (*attribute->patch)(3, 2) - (*attribute->patch)(2, 2);
            DCoordinate3 delta3 = (*attribute->patch)(3, 3) - (*attribute->patch)(2, 3);

            patch.SetData(1, 0, (*attribute->patch)(3, 0) + delta0);
            patch.SetData(1, 1, (*attribute->patch)(3, 1) + delta1);
            patch.SetData(1, 2, (*attribute->patch)(3, 2) + delta2);
            patch.SetData(1, 3, (*attribute->patch)(3, 3) + delta3);

            patch.SetData(2, 0, (*attribute->patch)(3, 0) + 2 * delta0);
            patch.SetData(2, 1, (*attribute->patch)(3, 1) + 2 * delta1);
            patch.SetData(2, 2, (*attribute->patch)(3, 2) + 2 * delta2);
            patch.SetData(2, 3, (*attribute->patch)(3, 3) + 2 * delta3);

            patch.SetData(3, 0, (*attribute->patch)(3, 0) + 3 * delta0);
            patch.SetData(3, 1, (*attribute->patch)(3, 1) + 3 * delta1);
            patch.SetData(3, 2, (*attribute->patch)(3, 2) + 3 * delta2);
            patch.SetData(3, 3, (*attribute->patch)(3, 3) + 3 * delta3);

            _attributes[index].connection_type[direction] = N;
            _attributes[patch_count].neighbours[N] = &_attributes[index];
            _attributes[patch_count].connection_type[N] = direction;
        }
        break;
    }

    _attributes[index].neighbours[direction] = &_attributes[patch_count];

    if (!_attributes[index].UpdateImageAndVBO() ||
        !_attributes[patch_count].UpdateImageAndVBO())
    {
        std::cout << "Error updating after ContinueExistingPatch!" << std::endl;
        return GL_FALSE;
    }

    return GL_TRUE;
}

Matrix<FOAHCompositePatch3::Pair> FOAHCompositePatch3::GetIndexesFromDirection(Direction direction){
    Matrix<Pair> result(2, 4);

    switch(direction){
        case (N):
        {
            result(0, 0).column_index = 0;
            result(0, 1).column_index = 1;
            result(0, 2).column_index = 2;
            result(0, 3).column_index = 3;
            result(0, 0).row_index = 0;
            result(0, 1).row_index = 0;
            result(0, 2).row_index = 0;
            result(0, 3).row_index = 0;
            result(1, 0).column_index = 0;
            result(1, 1).column_index = 1;
            result(1, 2).column_index = 2;
            result(1, 3).column_index = 3;
            result(1, 0).row_index = 1;
            result(1, 1).row_index = 1;
            result(1, 2).row_index = 1;
            result(1, 3).row_index = 1;
        }
        break;
        case (W):
        {
            result(0, 0).column_index = 0;
            result(0, 1).column_index = 0;
            result(0, 2).column_index = 0;
            result(0, 3).column_index = 0;
            result(0, 0).row_index = 0;
            result(0, 1).row_index = 1;
            result(0, 2).row_index = 2;
            result(0, 3).row_index = 3;
            result(1, 0).column_index = 1;
            result(1, 1).column_index = 1;
            result(1, 2).column_index = 1;
            result(1, 3).column_index = 1;
            result(1, 0).row_index = 0;
            result(1, 1).row_index = 1;
            result(1, 2).row_index = 2;
            result(1, 3).row_index = 3;
        }
        break;
        case (S):
        {
            result(0, 0).column_index = 0;
            result(0, 1).column_index = 1;
            result(0, 2).column_index = 2;
            result(0, 3).column_index = 3;
            result(0, 0).row_index = 3;
            result(0, 1).row_index = 3;
            result(0, 2).row_index = 3;
            result(0, 3).row_index = 3;
            result(1, 0).column_index = 0;
            result(1, 1).column_index = 1;
            result(1, 2).column_index = 2;
            result(1, 3).column_index = 3;
            result(1, 0).row_index = 2;
            result(1, 1).row_index = 2;
            result(1, 2).row_index = 2;
            result(1, 3).row_index = 2;
        }
        break;
        case (E):
        {
            result(0, 0).column_index = 3;
            result(0, 1).column_index = 3;
            result(0, 2).column_index = 3;
            result(0, 3).column_index = 3;
            result(0, 0).row_index = 0;
            result(0, 1).row_index = 1;
            result(0, 2).row_index = 2;
            result(0, 3).row_index = 3;
            result(1, 0).column_index = 2;
            result(1, 1).column_index = 2;
            result(1, 2).column_index = 2;
            result(1, 3).column_index = 2;
            result(1, 0).row_index = 0;
            result(1, 1).row_index = 1;
            result(1, 2).row_index = 2;
            result(1, 3).row_index = 3;
        }
        break;
    }
    return result;
}

GLboolean FOAHCompositePatch3::MergeExistingPatches(GLuint index_0, Direction direction_0, GLuint index_1, Direction direction_1){

    if(direction_0 == NW || direction_0 == SW || direction_0 == SE || direction_0 == NE || direction_1 == NW || direction_1 == SW || direction_1 == SE || direction_1 == NE){
        return GL_FALSE;
    }

    if(index_0 >= _attributes.size() && index_1 >= _attributes.size()){
        std::cout << "Patch index invalid!" << std::endl;
        return GL_FALSE;
    }

    PatchAttributes* attribute_0 = &_attributes[index_0];
    PatchAttributes* attribute_1 = &_attributes[index_1];

    if (attribute_0->neighbours[direction_0] || attribute_1->neighbours[direction_1])
    {
        std::cout << "Patch already has a neighbor in given direction!";
        return GL_FALSE;
    }

    Matrix<Pair> first_indexes = GetIndexesFromDirection(direction_0);
    Matrix<Pair> second_indexes = GetIndexesFromDirection(direction_1);
    DCoordinate3 temp;
    for(GLuint i = 0; i < 4; ++i){
        temp = ((*attribute_0->patch)(first_indexes(1, i).row_index, first_indexes(1, i).column_index) + (*attribute_1->patch)(second_indexes(1, i).row_index, second_indexes(1, i).column_index)) / 2.0f;
        (*attribute_0->patch)(first_indexes(0, i).row_index, first_indexes(0, i).column_index) = temp;
        (*attribute_1->patch)(second_indexes(0, i).row_index, second_indexes(0, i).column_index) = temp;
    }

    //Set neighbours!!!

    _attributes[index_0].connection_type[direction_0] = direction_1;
    _attributes[index_0].neighbours[direction_0] = &_attributes[index_1];
    _attributes[index_1].connection_type[direction_1] = direction_0;
    _attributes[index_1].neighbours[direction_1] = &_attributes[index_0];


    if (!_attributes[index_0].UpdateImageAndVBO() ||
        !_attributes[index_1].UpdateImageAndVBO())
    {
        std::cout << "Error updating after MergeExistingPatches!" << std::endl;
        return GL_FALSE;
    }


    return GL_TRUE;
}

GLboolean FOAHCompositePatch3::JoinExistingPatches(GLuint index_0, Direction direction_0, GLuint index_1, Direction direction_1){

    if(direction_0 == NW || direction_0 == SW || direction_0 == SE || direction_0 == NE || direction_1 == NW || direction_1 == SW || direction_1 == SE || direction_1 == NE){
        return GL_FALSE;
    }

    if(index_0 >= _attributes.size() && index_1 >= _attributes.size()){
        std::cout << "Patch index invalid!" << std::endl;
        return GL_FALSE;
    }

    PatchAttributes* attribute_0 = &_attributes[index_0];
    PatchAttributes* attribute_1 = &_attributes[index_1];

    if (attribute_0->neighbours[direction_0] || attribute_1->neighbours[direction_1])
    {
        std::cout << "Patch already has a neighbor in given direction!";
        return GL_FALSE;
    }

    size_t patch_count = _attributes.size();
    _attributes.resize(patch_count + 1);
    _attributes[patch_count].patch = new FirstOrderAlgebraicHyperbolicPatch();

    FirstOrderAlgebraicHyperbolicPatch &patch = *_attributes[patch_count].patch;

    Matrix<Pair> first_indexes = GetIndexesFromDirection(direction_0);
    Matrix<Pair> second_indexes = GetIndexesFromDirection(direction_1);

    patch(0, 0) = (*attribute_0->patch)(first_indexes(0, 0).row_index, first_indexes(0, 0).column_index);
    patch(1, 0) = (*attribute_0->patch)(first_indexes(0, 1).row_index, first_indexes(0, 1).column_index);
    patch(2, 0) = (*attribute_0->patch)(first_indexes(0, 2).row_index, first_indexes(0, 2).column_index);
    patch(3, 0) = (*attribute_0->patch)(first_indexes(0, 3).row_index, first_indexes(0, 3).column_index);

    patch(0, 3) = (*attribute_0->patch)(second_indexes(0, 0).row_index, first_indexes(0, 0).column_index);
    patch(1, 3) = (*attribute_0->patch)(second_indexes(0, 1).row_index, first_indexes(0, 1).column_index);
    patch(2, 3) = (*attribute_0->patch)(second_indexes(0, 2).row_index, first_indexes(0, 2).column_index);
    patch(3, 3) = (*attribute_0->patch)(second_indexes(0, 3).row_index, first_indexes(0, 3).column_index);

    patch(0, 1) = patch(0, 0) + ((*attribute_0->patch)(first_indexes(0, 0).row_index, first_indexes(0, 0).column_index) - (*attribute_0->patch)(first_indexes(1, 0).row_index, first_indexes(1, 0).column_index));
    patch(1, 1) = patch(1, 0) + ((*attribute_0->patch)(first_indexes(0, 1).row_index, first_indexes(0, 1).column_index) - (*attribute_0->patch)(first_indexes(1, 1).row_index, first_indexes(1, 1).column_index));
    patch(2, 1) = patch(2, 0) + ((*attribute_0->patch)(first_indexes(0, 2).row_index, first_indexes(0, 2).column_index) - (*attribute_0->patch)(first_indexes(1, 2).row_index, first_indexes(1, 2).column_index));
    patch(3, 1) = patch(3, 0) + ((*attribute_0->patch)(first_indexes(0, 3).row_index, first_indexes(0, 3).column_index) - (*attribute_0->patch)(first_indexes(1, 3).row_index, first_indexes(1, 3).column_index));

    patch(0, 2) = patch(0, 3) + ((*attribute_0->patch)(second_indexes(0, 0).row_index, second_indexes(0, 0).column_index) - (*attribute_0->patch)(second_indexes(1, 0).row_index, second_indexes(1, 0).column_index));
    patch(1, 2) = patch(1, 3) + ((*attribute_0->patch)(second_indexes(0, 1).row_index, second_indexes(0, 1).column_index) - (*attribute_0->patch)(second_indexes(1, 1).row_index, second_indexes(1, 1).column_index));
    patch(2, 2) = patch(2, 3) + ((*attribute_0->patch)(second_indexes(0, 2).row_index, second_indexes(0, 2).column_index) - (*attribute_0->patch)(second_indexes(1, 2).row_index, second_indexes(1, 2).column_index));
    patch(3, 2) = patch(3, 3) + ((*attribute_0->patch)(second_indexes(0, 3).row_index, second_indexes(0, 3).column_index) - (*attribute_0->patch)(second_indexes(1, 3).row_index, second_indexes(1, 3).column_index));

    DCoordinate3 temp;
    for(GLuint i = 0; i < 4; ++i){
        temp = ((*attribute_0->patch)(first_indexes(1, i).row_index, first_indexes(1, i).column_index) + (*attribute_1->patch)(second_indexes(1, i).row_index, second_indexes(1, i).column_index)) / 2;
        (*attribute_0->patch)(first_indexes(0, i).row_index, first_indexes(0, i).column_index) = temp;
        (*attribute_1->patch)(second_indexes(0, i).row_index, second_indexes(0, i).column_index) = temp;
    }

    //Set neighbours!!!
    _attributes[index_0].connection_type[direction_0] = direction_1;
    _attributes[index_0].neighbours[direction_0] = &_attributes[index_1];
    _attributes[index_1].connection_type[direction_1] = direction_0;
    _attributes[index_1].neighbours[direction_1] = &_attributes[index_0];

    if (!_attributes[index_0].UpdateImageAndVBO() ||
        !_attributes[index_1].UpdateImageAndVBO())
    {
        std::cout << "Error updating after JoinExistingPatches!" << std::endl;
        return GL_FALSE;
    }

    return GL_TRUE;
}
DCoordinate3 FOAHCompositePatch3::getPoint(GLuint patchIndex, GLuint patchPointX, GLuint patchPointY) {
    DCoordinate3 res;
    _attributes[patchIndex].patch->GetData(patchPointX,patchPointY,res);
    return res;

GLvoid FOAHCompositePatch3::pushPatch(GLuint index, GLuint direction)
{
    _attributes[index].push(direction, nullptr);
}

GLvoid FOAHCompositePatch3::pullPatch(GLuint index, GLuint direction)
{
    _attributes[index].pull(direction, nullptr);
}
