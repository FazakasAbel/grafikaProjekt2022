#include "../Core/FOAHCompositePatch.h"

namespace cagd{
GLboolean FOAHCompositePatch3::ContinueExistingPatch(GLuint index, Direction direction){
    if(direction == NW || direction == SW || direction == SE || direction == NE){
        return GL_FALSE;
    }

    if(index >= _attributes.size()){
        cout << "Patch index invalid!" << endl;
        return GL_FALSE;
    }

    PatchAttributes* attribute = &_attributes[index];
    if (attribute->neighbours[direction])
    {
        cout << "Patch already has a neighbor in given direction!";
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

        }
        break;
    }

    //Set neighbours!!!
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
}

GLboolean FOAHCompositePatch3::MergeExistingPatches(GLuint index_0, Direction direction_0, GLuint index_1, Direction direction_1){

    if(direction_0 == NW || direction_0 == SW || direction_0 == SE || direction_0 == NE || direction_1 == NW || direction_1 == SW || direction_1 == SE || direction_1 == NE){
        return GL_FALSE;
    }

    if(index_0 >= _attributes.size() && index_1 >= _attributes.size()){
        cout << "Patch index invalid!" << endl;
        return GL_FALSE;
    }

    PatchAttributes* attribute_0 = &_attributes[index_0];
    PatchAttributes* attribute_1 = &_attributes[index_1];

    if (attribute_0->neighbours[direction_0] || attribute_1->neighbours[direction_1])
    {
        cout << "Patch already has a neighbor in given direction!";
        return GL_FALSE;
    }

    Matrix<Pair> first_indexes = GetIndexesFromDirection(direction_0);
    Matrix<Pair> second_indexes = GetIndexesFromDirection(direction_1);
    DCoordinate3 temp;
    for(GLuint i = 0; i < 4; ++i){
        temp = ((*attribute_0->patch)(first_indexes(1, i).row_index, first_indexes(1, i).column_index) + (*attribute_0->patch)(second_indexes(1, i).row_index, second_indexes(1, i).column_index)) / 2;
        (*attribute_0->patch)(first_indexes(0, i).row_index, first_indexes(0, i).column_index) = temp;
        (*attribute_1->patch)(second_indexes(0, i).row_index, second_indexes(0, i).column_index) = temp;
    }

    //Set neighbours!!!
}

GLboolean FOAHCompositePatch3::JoinExistingPatches(GLuint index_0, Direction direction_0, GLuint index_1, Direction direction_1){

    if(direction_0 == NW || direction_0 == SW || direction_0 == SE || direction_0 == NE || direction_1 == NW || direction_1 == SW || direction_1 == SE || direction_1 == NE){
        return GL_FALSE;
    }

    if(index_0 >= _attributes.size() && index_1 >= _attributes.size()){
        cout << "Patch index invalid!" << endl;
        return GL_FALSE;
    }

    PatchAttributes* attribute_0 = &_attributes[index_0];
    PatchAttributes* attribute_1 = &_attributes[index_1];

    if (attribute_0->neighbours[direction_0] || attribute_1->neighbours[direction_1])
    {
        cout << "Patch already has a neighbor in given direction!";
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
        temp = ((*attribute_0->patch)(first_indexes(1, i).row_index, first_indexes(1, i).column_index) + (*attribute_0->patch)(second_indexes(1, i).row_index, second_indexes(1, i).column_index)) / 2;
        (*attribute_0->patch)(first_indexes(0, i).row_index, first_indexes(0, i).column_index) = temp;
        (*attribute_1->patch)(second_indexes(0, i).row_index, second_indexes(0, i).column_index) = temp;
    }

    //Set neighbours!!!
}
}


