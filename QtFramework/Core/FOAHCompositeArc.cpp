#include "FOAHCompositeArc.h"
#include "Core/Exceptions.h"
#if !defined(__APPLE__)
#include <GL/glu.h>
#endif
#include <iostream>

using namespace std;
using namespace cagd;

FOAHCompositeArc::ArcAttributes::ArcAttributes() : arc(nullptr), image(nullptr), previous(nullptr), next(nullptr), color(nullptr)
{
}

FOAHCompositeArc::ArcAttributes::ArcAttributes(FirstOrderAlgebraicHyperbolicArc3& arc, Color4& color)
{
    this->arc = new FirstOrderAlgebraicHyperbolicArc3(arc);
    image = this->arc->GenerateImage( 2, 200, GL_STATIC_DRAW);
    this->color = new Color4(color);
    this->previous = nullptr;
    this->next = nullptr;
}

FOAHCompositeArc::ArcAttributes::ArcAttributes(const ArcAttributes& arcAttributes) : previous(arcAttributes.previous), next(arcAttributes.next)
{
    this->arc = new FirstOrderAlgebraicHyperbolicArc3(*arcAttributes.arc);
    this->image = new GenericCurve3(*arcAttributes.image);
    this->color = arcAttributes.color;
    this->next_connection_type = arcAttributes.next_connection_type;
    this->previous_connection_type = arcAttributes.previous_connection_type;
}

FOAHCompositeArc::ArcAttributes& FOAHCompositeArc::ArcAttributes::operator =(const ArcAttributes& rhs)
{
    if(&rhs == this){
        return *this;
    }

    if(rhs.arc){
        this->arc = new FirstOrderAlgebraicHyperbolicArc3(*rhs.arc);
    }

    if(rhs.image){
        this->image = new GenericCurve3(*rhs.image);
    }

    if(rhs.color){
        this->color = rhs.color;
    }

    this->next_connection_type = rhs.next_connection_type;
    this->previous_connection_type = rhs.previous_connection_type;
    this->previous = rhs.previous;
    this->next = rhs.next;

    return *this;
}


FOAHCompositeArc::ArcAttributes::~ArcAttributes()
{
    if(arc){
        delete arc;
        arc = nullptr;
    }

    if(image){
        delete image;
        image = nullptr;
    }

    if(color){
        delete color;
        color = nullptr;
    }
}

FOAHCompositeArc::FOAHCompositeArc(GLdouble alpha, GLuint minimal_arc_count_to_be_reserved) : _alpha(alpha)
{
    _attributes.reserve(minimal_arc_count_to_be_reserved);
}

GLboolean FOAHCompositeArc::InsertNewArc()
{
    try{
        size_t arc_count = _attributes.size();
        _attributes.resize(arc_count + 1);
        _attributes[arc_count].arc = new FirstOrderAlgebraicHyperbolicArc3();
        _attributes[arc_count].color = new Color4(1.0f, 0.0f, 0.0f);

        FirstOrderAlgebraicHyperbolicArc3 &newArc = *_attributes[arc_count].arc;
        newArc[0] = DCoordinate3(3, 0, 0);
        newArc[1] = DCoordinate3(1, 1, 0);
        newArc[2] = DCoordinate3(2, 2, 0);
        newArc[3] = DCoordinate3(3, 2, 0);
        newArc.UpdateVertexBufferObjectsOfData();

        _attributes[arc_count].image = newArc.GenerateImage(2, 200);
        GenericCurve3 &image = *_attributes[arc_count].image;
        image.UpdateVertexBufferObjects(1);

        return GL_TRUE;
    }
    catch(Exception e){
        std::cout << "InsertNewArc error!" << std::endl;
        return GL_FALSE;
    }
}

GLboolean FOAHCompositeArc::RenderAllArcs(GLuint order, GLenum render_mode) const
{
    for(auto& arcAttr : _attributes)
    {
        if(arcAttr.image)
        {
            glColor3f(arcAttr.color->r(), arcAttr.color->g(), arcAttr.color->b());
            arcAttr.image->RenderDerivatives(order, render_mode);
        }
        else
        {
            return GL_FALSE;
        }
    }

    return GL_TRUE;
}

GLboolean FOAHCompositeArc::RenderSelectedArc(GLuint index, GLuint order, GLenum render_mode) const
{
    if(_attributes[index].image){
        glColor3f(_attributes[index].color->r(), _attributes[index].color->g(), _attributes[index].color->b());
        _attributes[index].image->RenderDerivatives(order, render_mode);
        _attributes[index].arc->RenderData(render_mode);
    }
    else{
        return GL_FALSE;
    }

    return GL_TRUE;
}

GLboolean FOAHCompositeArc::RenderAllArcData(GLenum render_mode) const
{
    for (auto& arcAttr : _attributes)
    {
        glColor3f(arcAttr.color->r(), arcAttr.color->g(), arcAttr.color->b());
        arcAttr.arc->RenderData(render_mode);
    }

    return GL_TRUE;
}

GLboolean FOAHCompositeArc::ContinueExisitingArc(GLuint index, Direction direction)
{
    if (index >= _attributes.size())
    {
        cout << "Arc index invalid!" << endl;
        return GL_FALSE;
    }

    ArcAttributes* attribute = &_attributes[index];
    if ((direction == LEFT && attribute->previous) || (direction == RIGHT && attribute->next))
    {
        cout << "Arc already has a neighbor in given direction!";
        return GL_FALSE;
    }

    size_t arc_count = _attributes.size();
    _attributes.resize(arc_count + 1);
    _attributes[arc_count].arc = new FirstOrderAlgebraicHyperbolicArc3();
    _attributes[arc_count].color = new Color4(0.8f, 0.0f, 0.6f);

    FirstOrderAlgebraicHyperbolicArc3 &newArc = *_attributes[arc_count].arc;
    if (direction == LEFT)
    {
        newArc[3] = (*attribute->arc)[0];
        newArc[2] = 2 * newArc[3] - (*attribute->arc)[1];
        newArc[1] = 2 * newArc[2] - newArc[3];
        newArc[0] = 2 * newArc[1] - newArc[2];

        attribute->previous = &_attributes[arc_count];
        _attributes[arc_count].next = attribute;
    }
    else if (direction == RIGHT)
    {
        newArc[0] = (*attribute->arc)[3];
        newArc[1] = 2 * newArc[0] - (*attribute->arc)[2];
        newArc[2] = 2 * newArc[1] - newArc[0];
        newArc[3] = 2 * newArc[2] - newArc[1];

        attribute->next = &_attributes[arc_count];
        _attributes[arc_count].previous = attribute;
    }

    if (!newArc.UpdateVertexBufferObjectsOfData())
        throw Exception("Could not update VBO of arc's data!");

    _attributes[arc_count].image = newArc.GenerateImage(2, 200);
    if (!_attributes[arc_count].image)
        throw Exception("Could not generate image of arc!");

    if(!_attributes[arc_count].image->UpdateVertexBufferObjects(1))
        throw Exception("Could not update VBO of arc image!");

    return GL_TRUE;
}

GLboolean FOAHCompositeArc::JoinExistingArcs(GLuint index_0, Direction direction_0, GLuint index_1, Direction direction_1)
{
    // TODO: test
    if (index_0 >= _attributes.size() || index_1 >= _attributes.size())
    {
        cout << "Arc index is invalid!" << endl;
        return GL_FALSE;
    }

    ArcAttributes &attribute_0 = _attributes[index_0];
    ArcAttributes &attribute_1 = _attributes[index_1];

    if ((direction_0 == LEFT && attribute_0.previous) ||
        (direction_0 == RIGHT && attribute_0.next) ||
        (direction_1 == LEFT && attribute_1.previous) ||
        (direction_1 == RIGHT && attribute_1.next))
    {
        cout << "Arc already has a neighbor in given direction!" << endl;
        return GL_FALSE;
    }

    size_t arc_count = _attributes.size();
    _attributes.resize(arc_count + 1);

    _attributes[arc_count].arc = new FirstOrderAlgebraicHyperbolicArc3();
    _attributes[arc_count].color = new Color4(0.5f, 0.0f, 0.9f);
    _attributes[arc_count].previous = &attribute_0;
    _attributes[arc_count].next = &attribute_1;

    FirstOrderAlgebraicHyperbolicArc3 &joiningArc = *_attributes[arc_count].arc;

    if (direction_0 == LEFT)
    {
        joiningArc[0] = (*attribute_0.arc)[0];
        joiningArc[1] = 2 * joiningArc[0] - 2 * (*attribute_0.arc)[1];
        attribute_0.previous = &_attributes[arc_count];
    }
    else if (direction_0 == RIGHT)
    {
        joiningArc[0] = (*attribute_0.arc)[3];
        joiningArc[1] = 2 * joiningArc[0] - 2 * (*attribute_0.arc)[2];
        attribute_0.next = &_attributes[arc_count];
    }

    if (direction_1 == LEFT)
    {
        joiningArc[3] = (*attribute_1.arc)[0];
        joiningArc[2] = joiningArc[3] - 2 * (*attribute_1.arc)[1];
        attribute_1.previous = &_attributes[arc_count];
    }
    else if (direction_1 == RIGHT)
    {
        joiningArc[3] = (*attribute_1.arc)[3];
        joiningArc[2] = joiningArc[3] - 2 * (*attribute_1.arc)[2];
        attribute_1.next = &_attributes[arc_count];
    }

    if (!joiningArc.UpdateVertexBufferObjectsOfData())
        throw Exception("Could not update VBO of joining arc's data!");

    _attributes[arc_count].image = joiningArc.GenerateImage(2, 200);
    if (!_attributes[arc_count].image)
        throw Exception("Could not generate image of joining arc!");

    if (!_attributes[arc_count].image->UpdateVertexBufferObjects(1))
        throw Exception("Could not update VBO of joing arc image!");


    return GL_TRUE;
}

FOAHCompositeArc::~FOAHCompositeArc()
{
    for(auto& arcAttr : _attributes){
        arcAttr.image->DeleteVertexBufferObjects();
        arcAttr.arc->DeleteVertexBufferObjectsOfData();
    }
    _attributes.clear();
}
