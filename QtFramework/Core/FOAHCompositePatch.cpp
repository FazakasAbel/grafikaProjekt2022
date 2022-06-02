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
        if ((*u_curves)[i])
            (*u_curves)[i]->DeleteVertexBufferObjects();
        if (!(*u_curves)[i]->UpdateVertexBufferObjects(1))
            return GL_FALSE;

        if ((*v_curves)[i])
            (*v_curves)[i]->DeleteVertexBufferObjects();
        if (!(*v_curves)[i]->UpdateVertexBufferObjects(1))
            return GL_FALSE;
    }

    return GL_TRUE;
}

GLboolean FOAHCompositePatch3::PatchAttributes::UpdateImageAndVBO()
{
    if (patch)
        patch->DeleteVertexBufferObjectsOfData();

    if (!patch->UpdateVertexBufferObjectsOfData())
    {
        std::cout << "Error updating VBO of patch data!" << std::endl;
        return GL_FALSE;
    }

    if (image)
        image->DeleteVertexBufferObjects();

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

            if (_attributes[index].neighbours[W])
            {
                _attributes[patch_count].neighbours[SW] = _attributes[index].neighbours[W];
                _attributes[patch_count].connection_type[SW] = NE;
                _attributes[index].neighbours[W]->neighbours[NE] = &_attributes[patch_count];
                _attributes[index].neighbours[W]->neighbours[NE]->connection_type[NE] = SW;
            }
            if (_attributes[index].neighbours[E])
            {
                _attributes[patch_count].neighbours[SE] = _attributes[index].neighbours[E];
                _attributes[patch_count].connection_type[SE] = NW;
                _attributes[index].neighbours[E]->neighbours[NW] = &_attributes[patch_count];
                _attributes[index].neighbours[E]->neighbours[NW]->connection_type[NW] = SE;
            }

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

            if (_attributes[index].neighbours[N])
            {
                _attributes[patch_count].neighbours[NE] = _attributes[index].neighbours[N];
                _attributes[patch_count].connection_type[NE] = SW;
                _attributes[index].neighbours[N]->neighbours[SW] = &_attributes[patch_count];
                _attributes[index].neighbours[N]->neighbours[SW]->connection_type[SW] = NE;
            }
            if (_attributes[index].neighbours[S])
            {
                _attributes[patch_count].neighbours[SE] = _attributes[index].neighbours[S];
                _attributes[patch_count].connection_type[SE] = NW;
                _attributes[index].neighbours[S]->neighbours[NW] = &_attributes[patch_count];
                _attributes[index].neighbours[S]->neighbours[NW]->connection_type[NW] = SE;
            }
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

            if (_attributes[index].neighbours[N])
            {
                _attributes[patch_count].neighbours[NW] = _attributes[index].neighbours[N];
                _attributes[patch_count].connection_type[NW] = SE;
                _attributes[index].neighbours[N]->neighbours[SE] = &_attributes[patch_count];
                _attributes[index].neighbours[N]->neighbours[SE]->connection_type[SE] = NW;
            }
            if (_attributes[index].neighbours[S])
            {
                _attributes[patch_count].neighbours[SW] = _attributes[index].neighbours[S];
                _attributes[patch_count].connection_type[SW] = NE;
                _attributes[index].neighbours[S]->neighbours[NE] = &_attributes[patch_count];
                _attributes[index].neighbours[S]->neighbours[NE]->connection_type[NE] = SW;
            }
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

            if (_attributes[index].neighbours[W])
            {
                _attributes[patch_count].neighbours[NW] = _attributes[index].neighbours[W];
                _attributes[patch_count].connection_type[NW] = SE;
                _attributes[index].neighbours[W]->neighbours[SE] = &_attributes[patch_count];
                _attributes[index].neighbours[W]->neighbours[SE]->connection_type[SE] = NW;
            }
            if (_attributes[index].neighbours[E])
            {
                _attributes[patch_count].neighbours[NE] = _attributes[index].neighbours[E];
                _attributes[patch_count].connection_type[NE] = SW;
                _attributes[index].neighbours[E]->neighbours[SW] = &_attributes[patch_count];
                _attributes[index].neighbours[E]->neighbours[SW]->connection_type[SW] =NE;
            }
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

GLvoid FOAHCompositePatch3::rotateMatrixLeft(Matrix<Pair>* mat)
{
    int n = mat->GetColumnCount();
    // Consider all squares one by one
    for (int x = 0; x < n / 2; x++) {
        // Consider elements in group
        // of 4 in current square
        for (int y = x; y < n - x - 1; y++) {
        // Store current cell in
        // temp variable
        Pair temp = (*mat)(x,y);

        // Move values from right to top
        (*mat)(x,y) = (*mat)(y,n - 1 - x);

        // Move values from bottom to right
        (*mat)(y,n - 1 - x) = (*mat)(n - 1 - x,n - 1 - y);

        // Move values from left to bottom
        (*mat)(n - 1 - x,n - 1 - y) = (*mat)(n - 1 - y,x);

        // Assign temp to left
        (*mat)(n - 1 - y,x) = temp;
        }
    }
}

GLvoid FOAHCompositePatch3::rotateMatrixRight(Matrix<Pair>* mat)
{
    int n = mat->GetColumnCount();
    // Consider all squares one by one
    for (int i = 0; i < n / 2; i++) {
            for (int j = i; j < n - i - 1; j++) {

                // Swap elements of each cycle
                // in clockwise direction
                Pair temp = (*mat)(i,j);
                (*mat)(i,j) = (*mat)(n - 1 - j,i);
                (*mat)(n - 1 - j,i) = (*mat)(n - 1 - i,n - 1 - j);
                (*mat)(n - 1 - i,n - 1 - j) = (*mat)(j,n - 1 - i);
                (*mat)(j,n - 1 - i) = temp;
            }
        }
}

Matrix<FOAHCompositePatch3::Pair> FOAHCompositePatch3::GetIndexesFromDirection(Direction direction, Direction new_direction){
    Matrix<Pair> result(2, 4);

    Matrix<Pair>* matrix = new Matrix<Pair>(4,4);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            (*matrix)(i,j).row_index = i;
            (*matrix)(i,j).column_index = 3 - j;
        }

    if (new_direction == N)
    {
        switch (direction)
        {
            case (E):
                rotateMatrixRight(matrix);
            case (S):
                rotateMatrixRight(matrix);
            case (W):
                rotateMatrixRight(matrix);
        }

        for (int i = 0; i < 4; i++)
        {
            result(0,i) = (*matrix)(0,i);
            result(1,i) = (*matrix)(1,i);
        }
    }

    if (new_direction == S)
    {
        switch (direction)
        {
            case (E):
                rotateMatrixLeft(matrix);
            case (N):
                rotateMatrixLeft(matrix);
            case (W):
                rotateMatrixLeft(matrix);
        }

        for (int i = 0; i < 4; i++)
        {
            result(0,i) = (*matrix)(3,i);
            result(1,i) = (*matrix)(2,i);
        }

    }

    if (new_direction == E)
    {
        switch (direction)
        {
            case (S):
                rotateMatrixLeft(matrix);
            case (W):
                rotateMatrixLeft(matrix);
            case (N):
                rotateMatrixLeft(matrix);
        }

        for (int i = 0; i < 4; i++)
        {
            result(0,i) = (*matrix)(i,0);
            result(1,i) = (*matrix)(i,1);
        }

    }

    if (new_direction == W)
    {
        switch (direction)
        {
            case (N):
                rotateMatrixRight(matrix);
            case (E):
                rotateMatrixRight(matrix);
            case (S):
                rotateMatrixRight(matrix);
        }

        for (int i = 0; i < 4; i++)
        {
            result(0,i) = (*matrix)(i,3);
            result(1,i) = (*matrix)(i,2);
        }

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

    Matrix<Pair> first_indexes = GetIndexesFromDirection(direction_0, N);
    Matrix<Pair> second_indexes = GetIndexesFromDirection(direction_1, S);

    //  TODO:  remove testing

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
            std::cout << first_indexes(i,j).row_index << "," << first_indexes(i,j).column_index << "  ";

        std::cout << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
            std::cout << second_indexes(i,j).row_index << "," << second_indexes(i,j).column_index << "  ";

        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "--------------------------" << std::endl;







    DCoordinate3 temp;
    for(GLuint i = 0; i < 4; ++i){
        temp = ((*attribute_0->patch)(first_indexes(1, i).row_index, first_indexes(1, i).column_index) + (*attribute_1->patch)(second_indexes(1, i).row_index, second_indexes(1, i).column_index)) / 2.0;
//        (*attribute_0->patch)(first_indexes(0, i).row_index, first_indexes(0, i).column_index) = temp;
//        (*attribute_1->patch)(second_indexes(0, i).row_index, second_indexes(0, i).column_index) = temp;
        setPoint(index_0 ,first_indexes(0, i).row_index, first_indexes(0, i).column_index, temp);
        setPoint(index_1 ,second_indexes(0, i).row_index, second_indexes(0, i).column_index, temp);
    }

    //Set neighbours!!!

    _attributes[index_0].connection_type[direction_0] = direction_1;
    _attributes[index_0].neighbours[direction_0] = &_attributes[index_1];
    _attributes[index_1].connection_type[direction_1] = direction_0;
    _attributes[index_1].neighbours[direction_1] = &_attributes[index_0];

    /*if(direction_0 == N){
        if(direction_1 == N){
           if(_attributes[index_1].neighbours[E]){
               _attributes[index_0].connection_type[direction_0] = direction_1;
               _attributes[index_0].neighbours[direction_0] = &_attributes[index_1];
               _attributes[index_1].connection_type[direction_1] = direction_0;
               _attributes[index_1].neighbours[direction_1] = &_attributes[index_0];
           }
        }

    }
    if(direction_0 == S){

    }
    if(direction_0 == E){

    }
    if(direction_0 == W){

    }*/

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

    Matrix<Pair> first_indexes = GetIndexesFromDirection(direction_0, W);
    Matrix<Pair> second_indexes = GetIndexesFromDirection(direction_1, E);

    patch(0, 0) = (*attribute_0->patch)(first_indexes(0, 0).row_index, first_indexes(0, 0).column_index);
    patch(1, 0) = (*attribute_0->patch)(first_indexes(0, 1).row_index, first_indexes(0, 1).column_index);
    patch(2, 0) = (*attribute_0->patch)(first_indexes(0, 2).row_index, first_indexes(0, 2).column_index);
    patch(3, 0) = (*attribute_0->patch)(first_indexes(0, 3).row_index, first_indexes(0, 3).column_index);

    patch(0, 3) = (*attribute_1->patch)(second_indexes(0, 0).row_index, second_indexes(0, 0).column_index);
    patch(1, 3) = (*attribute_1->patch)(second_indexes(0, 1).row_index, second_indexes(0, 1).column_index);
    patch(2, 3) = (*attribute_1->patch)(second_indexes(0, 2).row_index, second_indexes(0, 2).column_index);
    patch(3, 3) = (*attribute_1->patch)(second_indexes(0, 3).row_index, second_indexes(0, 3).column_index);

    patch(0, 1) = patch(0, 0) + ((*attribute_0->patch)(first_indexes(0, 0).row_index, first_indexes(0, 0).column_index) - (*attribute_0->patch)(first_indexes(1, 0).row_index, first_indexes(1, 0).column_index));
    patch(1, 1) = patch(1, 0) + ((*attribute_0->patch)(first_indexes(0, 1).row_index, first_indexes(0, 1).column_index) - (*attribute_0->patch)(first_indexes(1, 1).row_index, first_indexes(1, 1).column_index));
    patch(2, 1) = patch(2, 0) + ((*attribute_0->patch)(first_indexes(0, 2).row_index, first_indexes(0, 2).column_index) - (*attribute_0->patch)(first_indexes(1, 2).row_index, first_indexes(1, 2).column_index));
    patch(3, 1) = patch(3, 0) + ((*attribute_0->patch)(first_indexes(0, 3).row_index, first_indexes(0, 3).column_index) - (*attribute_0->patch)(first_indexes(1, 3).row_index, first_indexes(1, 3).column_index));

    patch(0, 2) = patch(0, 3) + ((*attribute_1->patch)(second_indexes(0, 0).row_index, second_indexes(0, 0).column_index) - (*attribute_1->patch)(second_indexes(1, 0).row_index, second_indexes(1, 0).column_index));
    patch(1, 2) = patch(1, 3) + ((*attribute_1->patch)(second_indexes(0, 1).row_index, second_indexes(0, 1).column_index) - (*attribute_1->patch)(second_indexes(1, 1).row_index, second_indexes(1, 1).column_index));
    patch(2, 2) = patch(2, 3) + ((*attribute_1->patch)(second_indexes(0, 2).row_index, second_indexes(0, 2).column_index) - (*attribute_1->patch)(second_indexes(1, 2).row_index, second_indexes(1, 2).column_index));
    patch(3, 2) = patch(3, 3) + ((*attribute_1->patch)(second_indexes(0, 3).row_index, second_indexes(0, 3).column_index) - (*attribute_1->patch)(second_indexes(1, 3).row_index, second_indexes(1, 3).column_index));


    //Set neighbours!!!
    _attributes[index_0].connection_type[direction_0] = W;
    _attributes[index_0].neighbours[direction_0] = &_attributes[patch_count];
    _attributes[index_1].connection_type[direction_1] = E;
    _attributes[index_1].neighbours[direction_1] = &_attributes[patch_count];

    _attributes[patch_count].neighbours[W] = &_attributes[index_0];
    _attributes[patch_count].neighbours[E] = &_attributes[index_1];
    _attributes[patch_count].connection_type[W] = direction_0;
    _attributes[patch_count].connection_type[E] = direction_1;

    if (!_attributes[index_0].UpdateImageAndVBO() ||
        !_attributes[index_1].UpdateImageAndVBO() ||
        !_attributes[patch_count].UpdateImageAndVBO())
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
}
GLuint FOAHCompositePatch3::getPatchCount()
{
    return _attributes.size();
}

GLvoid FOAHCompositePatch3::pushPatch(GLuint index, GLuint direction)
{
    _attributes[index].push(direction, nullptr);
}

GLvoid FOAHCompositePatch3::pullPatch(GLuint index, GLuint direction)
{
    _attributes[index].pull(direction, nullptr);
}

std::ostream& operator <<(std::ostream& lhs, FOAHCompositePatch3::Pair pair){
    lhs << "(" << pair.row_index << " " << pair.column_index << ")";
    return lhs;
}

GLvoid FOAHCompositePatch3::setPoint(GLuint patch_index, GLuint row, GLuint column, DCoordinate3 newPosition)
{
    // TODO: 3 eset: szel, kozepso, sarok
    DCoordinate3 point;
    _attributes[patch_index].patch->GetData(row, column, point);
    DCoordinate3 movement = newPosition - point;
    DCoordinate3 prev_pos = point;

    _attributes[patch_index].patch->SetData(row, column, newPosition);

    // TODO: szel
    if (row == 0) {
        if (_attributes[patch_index].neighbours[N]) {
            Matrix<Pair> firstIndexes = GetIndexesFromDirection(N, _attributes[patch_index].connection_type[N]);
            Matrix<Pair> secondIndexes = GetIndexesFromDirection(_attributes[patch_index].connection_type[N], N);

            _attributes[patch_index].patch->GetData(firstIndexes(1, column).row_index, firstIndexes(1, column).column_index, prev_pos);
            _attributes[patch_index].patch->SetData(firstIndexes(1, column).row_index, firstIndexes(1, column).column_index, prev_pos + movement);

            _attributes[patch_index].neighbours[N]->patch->GetData(secondIndexes(0, column).row_index, secondIndexes(0, column).column_index, prev_pos);
            _attributes[patch_index].neighbours[N]->patch->SetData(secondIndexes(0, column).row_index, secondIndexes(0, column).column_index, prev_pos + movement);
            _attributes[patch_index].neighbours[N]->patch->GetData(secondIndexes(1, column).row_index, secondIndexes(1, column).column_index, prev_pos);
            _attributes[patch_index].neighbours[N]->patch->SetData(secondIndexes(1, column).row_index, secondIndexes(1, column).column_index, prev_pos + movement);

            _attributes[patch_index].neighbours[N]->UpdateImageAndVBO();
        }
    }
    if (row == 3) {
        if (_attributes[patch_index].neighbours[S]) {
            Matrix<Pair> firstIndexes = GetIndexesFromDirection(S, _attributes[patch_index].connection_type[S]);
            Matrix<Pair> secondIndexes = GetIndexesFromDirection(_attributes[patch_index].connection_type[S], S);
            _attributes[patch_index].patch->GetData(firstIndexes(1, column).row_index, firstIndexes(1, column).column_index, prev_pos);
            _attributes[patch_index].patch->SetData(firstIndexes(1, column).row_index, firstIndexes(1, column).column_index, prev_pos + movement);

            _attributes[patch_index].neighbours[S]->patch->GetData(secondIndexes(0, column).row_index, secondIndexes(0, column).column_index, prev_pos);
            _attributes[patch_index].neighbours[S]->patch->SetData(secondIndexes(0, column).row_index, secondIndexes(0, column).column_index, prev_pos + movement);
            _attributes[patch_index].neighbours[S]->patch->GetData(secondIndexes(1, column).row_index, secondIndexes(1, column).column_index, prev_pos);
            _attributes[patch_index].neighbours[S]->patch->SetData(secondIndexes(1, column).row_index, secondIndexes(1, column).column_index, prev_pos + movement);

            _attributes[patch_index].neighbours[S]->UpdateImageAndVBO();
        }
    }
    if(column == 0){
        if (_attributes[patch_index].neighbours[W]) {
            Matrix<Pair> firstIndexes = GetIndexesFromDirection(W, _attributes[patch_index].connection_type[W]);
            Matrix<Pair> secondIndexes = GetIndexesFromDirection(_attributes[patch_index].connection_type[W], W);
            _attributes[patch_index].patch->GetData(firstIndexes(1, column).row_index, firstIndexes(1, column).column_index, prev_pos);
            _attributes[patch_index].patch->SetData(firstIndexes(1, column).row_index, firstIndexes(1, column).column_index, prev_pos + movement);

            _attributes[patch_index].neighbours[W]->patch->GetData(secondIndexes(0, column).row_index, secondIndexes(0, column).column_index, prev_pos);
            _attributes[patch_index].neighbours[W]->patch->SetData(secondIndexes(0, column).row_index, secondIndexes(0, column).column_index, prev_pos + movement);
            _attributes[patch_index].neighbours[W]->patch->GetData(secondIndexes(1, column).row_index, secondIndexes(1, column).column_index, prev_pos);
            _attributes[patch_index].neighbours[W]->patch->SetData(secondIndexes(1, column).row_index, secondIndexes(1, column).column_index, prev_pos + movement);

            _attributes[patch_index].neighbours[W]->UpdateImageAndVBO();
        }
    }
    if(column == 3){
        if (_attributes[patch_index].neighbours[E]) {
            Matrix<Pair> firstIndexes = GetIndexesFromDirection(E, _attributes[patch_index].connection_type[E]);
            Matrix<Pair> secondIndexes = GetIndexesFromDirection(_attributes[patch_index].connection_type[E], E);
            _attributes[patch_index].patch->GetData(firstIndexes(1, column).row_index, firstIndexes(1, column).column_index, prev_pos);
            _attributes[patch_index].patch->SetData(firstIndexes(1, column).row_index, firstIndexes(1, column).column_index, prev_pos + movement);

            _attributes[patch_index].neighbours[E]->patch->GetData(secondIndexes(0, column).row_index, secondIndexes(0, column).column_index, prev_pos);
            _attributes[patch_index].neighbours[E]->patch->SetData(secondIndexes(0, column).row_index, secondIndexes(0, column).column_index, prev_pos + movement);
            _attributes[patch_index].neighbours[E]->patch->GetData(secondIndexes(1, column).row_index, secondIndexes(1, column).column_index, prev_pos);
            _attributes[patch_index].neighbours[E]->patch->SetData(secondIndexes(1, column).row_index, secondIndexes(1, column).column_index, prev_pos + movement);

            _attributes[patch_index].neighbours[E]->UpdateImageAndVBO();
        }
    }

    if(column == 1){
        if (_attributes[patch_index].neighbours[W]) {
            Matrix<Pair> firstIndexes = GetIndexesFromDirection(W, _attributes[patch_index].connection_type[W]);
            Matrix<Pair> secondIndexes = GetIndexesFromDirection(_attributes[patch_index].connection_type[W], W);

            _attributes[patch_index].neighbours[W]->patch->GetData(secondIndexes(1, column).row_index, secondIndexes(1, column).column_index, prev_pos);
            _attributes[patch_index].neighbours[W]->patch->SetData(secondIndexes(1, column).row_index, secondIndexes(1, column).column_index, prev_pos - movement);

            _attributes[patch_index].neighbours[W]->UpdateImageAndVBO();
        }

    }

    if(column == 2){
        if (_attributes[patch_index].neighbours[E]) {
            Matrix<Pair> firstIndexes = GetIndexesFromDirection(E, _attributes[patch_index].connection_type[E]);
            Matrix<Pair> secondIndexes = GetIndexesFromDirection(_attributes[patch_index].connection_type[E], E);

            _attributes[patch_index].neighbours[E]->patch->GetData(secondIndexes(1, column).row_index, secondIndexes(1, column).column_index, prev_pos);
            _attributes[patch_index].neighbours[E]->patch->SetData(secondIndexes(1, column).row_index, secondIndexes(1, column).column_index, prev_pos - movement);

            _attributes[patch_index].neighbours[E]->UpdateImageAndVBO();
        }
    }
    if(row == 1){
        if (_attributes[patch_index].neighbours[N]) {
            Matrix<Pair> firstIndexes = GetIndexesFromDirection(N, _attributes[patch_index].connection_type[N]);
            Matrix<Pair> secondIndexes = GetIndexesFromDirection(_attributes[patch_index].connection_type[N], N);

            _attributes[patch_index].neighbours[N]->patch->GetData(secondIndexes(1, column).row_index, secondIndexes(1, column).column_index, prev_pos);
            _attributes[patch_index].neighbours[N]->patch->SetData(secondIndexes(1, column).row_index, secondIndexes(1, column).column_index, prev_pos - movement);

            _attributes[patch_index].neighbours[N]->UpdateImageAndVBO();
        }

    }

    if(row == 2){
        if (_attributes[patch_index].neighbours[S]) {
            Matrix<Pair> firstIndexes = GetIndexesFromDirection(S, _attributes[patch_index].connection_type[S]);
            Matrix<Pair> secondIndexes = GetIndexesFromDirection(_attributes[patch_index].connection_type[S], S);

            _attributes[patch_index].neighbours[S]->patch->GetData(secondIndexes(1, column).row_index, secondIndexes(1, column).column_index, prev_pos);
            _attributes[patch_index].neighbours[S]->patch->SetData(secondIndexes(1, column).row_index, secondIndexes(1, column).column_index, prev_pos - movement);

            _attributes[patch_index].neighbours[S]->UpdateImageAndVBO();
        }
    }
    // TODO: sarok

    // TODO:  kozep
    _attributes[patch_index].UpdateImageAndVBO();
}
