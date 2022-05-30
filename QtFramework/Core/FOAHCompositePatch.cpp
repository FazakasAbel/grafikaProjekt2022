#include "../Core/FOAHCompositePatch.h"

using namespace cagd;

GLboolean FOAHCompositePatch3::ContinueExistingPatch(GLuint index, Direction direction){
    if(direction == NW || direction == SW || direction == SE || direction == NE){
        return GL_FALSE;
    }

    if(index < _attributes.size()){
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
}
