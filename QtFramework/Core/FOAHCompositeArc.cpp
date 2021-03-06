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

GLuint FOAHCompositeArc::getArcCount(){
    return _attributes.size();
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
        attribute->previous_connection_type = RIGHT;
        _attributes[arc_count].next_connection_type = LEFT;
    }
    else if (direction == RIGHT)
    {
        newArc[0] = (*attribute->arc)[3];
        newArc[1] = 2 * newArc[0] - (*attribute->arc)[2];
        newArc[2] = 2 * newArc[1] - newArc[0];
        newArc[3] = 2 * newArc[2] - newArc[1];

        attribute->next = &_attributes[arc_count];
        _attributes[arc_count].previous = attribute;
        attribute->next_connection_type = LEFT;
        _attributes[arc_count].previous_connection_type = RIGHT;
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

GLvoid FOAHCompositeArc::ArcAttributes::push(GLuint axis){
    (*arc)[0][axis] += 1;
    (*arc)[1][axis] += 1;
    (*arc)[2][axis] += 1;
    (*arc)[3][axis] += 1;

    arc->DeleteVertexBufferObjectsOfData();
    arc->UpdateVertexBufferObjectsOfData();
    if(image){
        image->DeleteVertexBufferObjects();
    }
    image = arc->GenerateImage(2, 200);
    image->UpdateVertexBufferObjects(1);
}

GLvoid FOAHCompositeArc::ArcAttributes::pull(GLuint axis){
    (*arc)[0][axis] -= 1;
    (*arc)[1][axis] -= 1;
    (*arc)[2][axis] -= 1;
    (*arc)[3][axis] -= 1;

    arc->DeleteVertexBufferObjectsOfData();
    arc->UpdateVertexBufferObjectsOfData();
    if(image){
        image->DeleteVertexBufferObjects();
    }
    image = arc->GenerateImage(2, 200);
    image->UpdateVertexBufferObjects(1);
}

DCoordinate3 FOAHCompositeArc::getPoint(GLuint arcIndex, GLuint pointIndex){

    return (*_attributes[arcIndex].arc)[pointIndex];
}

GLvoid FOAHCompositeArc::setPoint(GLuint arcIndex, GLuint pointIndex, GLuint direction, GLdouble newValue){

    if(newValue != getPoint(arcIndex, pointIndex)[direction]){
        GLdouble delta = newValue - (*_attributes[arcIndex].arc)[pointIndex][direction];
        cout << delta << endl;

        _attributes[arcIndex].setPoint(pointIndex, direction, newValue);
        GLuint temp_point_index, temp_point_index_2;
        if(_attributes[arcIndex].next){

            if(pointIndex == 3){
                temp_point_index = _attributes[arcIndex].next_connection_type == LEFT ? 0 : 3;
                temp_point_index_2 = _attributes[arcIndex].next_connection_type == LEFT ? 1 : 2;

                (*_attributes[arcIndex].next->arc)[temp_point_index][direction] += delta;
                (*_attributes[arcIndex].next->arc)[temp_point_index_2][direction] += delta;
                (*_attributes[arcIndex].arc)[pointIndex - 1][direction] += delta;
            }

            if(pointIndex == 2){
                temp_point_index = _attributes[arcIndex].next_connection_type == LEFT ? 1 : 2;

                (*_attributes[arcIndex].next->arc)[temp_point_index][direction] -= delta;
            }

            _attributes[arcIndex].next->arc->UpdateVertexBufferObjectsOfData();
            _attributes[arcIndex].next->image = _attributes[arcIndex].next->arc->GenerateImage(2, 200);
            _attributes[arcIndex].next->image->UpdateVertexBufferObjects(1);

        }

        if(_attributes[arcIndex].previous){


            if(pointIndex == 0){
                temp_point_index = _attributes[arcIndex].previous_connection_type == RIGHT ? 3 :0;
                temp_point_index_2 = _attributes[arcIndex].previous_connection_type == RIGHT ? 2 : 1;

                (*_attributes[arcIndex].previous->arc)[temp_point_index][direction] += delta;
                (*_attributes[arcIndex].previous->arc)[temp_point_index_2][direction] += delta;
                (*_attributes[arcIndex].arc)[pointIndex + 1][direction] += delta;
            }

            if(pointIndex == 1){
                temp_point_index = _attributes[arcIndex].previous_connection_type == RIGHT ? 2 : 1;

                (*_attributes[arcIndex].previous->arc)[temp_point_index][direction] -= delta;
            }

            _attributes[arcIndex].previous->arc->UpdateVertexBufferObjectsOfData();
            _attributes[arcIndex].previous->image = _attributes[arcIndex].previous->arc->GenerateImage(2, 200);
            _attributes[arcIndex].previous->image->UpdateVertexBufferObjects(1);

        }
        _attributes[arcIndex].arc->UpdateVertexBufferObjectsOfData();
        _attributes[arcIndex].image = _attributes[arcIndex].arc->GenerateImage(2, 200);
        _attributes[arcIndex].image->UpdateVertexBufferObjects(1);
   }

}

GLvoid FOAHCompositeArc::ArcAttributes::setPoint(GLuint pointIndex, GLuint direction, GLdouble newValue){
    (*arc)[pointIndex][direction] = newValue;
}

FOAHCompositeArc::ArcAttributes& FOAHCompositeArc::getPrevious(GLuint index){
    return *(_attributes[index].previous);
}

FOAHCompositeArc::ArcAttributes& FOAHCompositeArc::getNext(GLuint index){
    return *(_attributes[index].next);
}

GLboolean FOAHCompositeArc::JoinExistingArcs(GLuint index_0, Direction direction_0, GLuint index_1, Direction direction_1)
{
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
        joiningArc[1] = 2 * joiningArc[0] - (*attribute_0.arc)[1];
        attribute_0.previous = &_attributes[arc_count];
        attribute_0.previous_connection_type = LEFT;
    }
    else if (direction_0 == RIGHT)
    {
        joiningArc[0] = (*attribute_0.arc)[3];
        joiningArc[1] = 2 * joiningArc[0] - (*attribute_0.arc)[2];
        attribute_0.next = &_attributes[arc_count];
        attribute_0.next_connection_type = LEFT;
    }

    if (direction_1 == LEFT)
    {
        joiningArc[3] = (*attribute_1.arc)[0];
        joiningArc[2] = 2 * joiningArc[3] - (*attribute_1.arc)[1];
        attribute_1.previous = &_attributes[arc_count];
        attribute_1.previous_connection_type = RIGHT;
    }
    else if (direction_1 == RIGHT)
    {
        joiningArc[3] = (*attribute_1.arc)[3];
        joiningArc[2] = 2 * joiningArc[3] - (*attribute_1.arc)[2];
        attribute_1.next = &_attributes[arc_count];
        attribute_1.next_connection_type = RIGHT;
    }

    if (!joiningArc.UpdateVertexBufferObjectsOfData())
        throw Exception("Could not update VBO of joining arc's data!");

    _attributes[arc_count].image = joiningArc.GenerateImage(2, 200);
    if (!_attributes[arc_count].image)
        throw Exception("Could not generate image of joining arc!");

    if (!_attributes[arc_count].image->UpdateVertexBufferObjects(1))
        throw Exception("Could not update VBO of joing arc image!");

    _attributes[arc_count].previous_connection_type = direction_0;
    _attributes[arc_count].next_connection_type = direction_1;

    return GL_TRUE;
}

GLboolean FOAHCompositeArc::MergeExistingArcs(GLuint index_0, Direction direction_0, GLuint index_1, Direction direction_1)
{
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

    DCoordinate3 join_point_0, join_point_1;

    if (direction_0 == LEFT)
        join_point_0 = (*attribute_0.arc)[1];
    else if (direction_0 == RIGHT)
        join_point_0 = (*attribute_0.arc)[2];

    if (direction_1 == LEFT)
        join_point_1 = (*attribute_1.arc)[1];
    else if (direction_1 == RIGHT)
        join_point_1 = (*attribute_1.arc)[2];

    DCoordinate3 midpoint = (join_point_0 + join_point_1) / 2.0f;

    if (direction_0 == LEFT)
    {
        (*attribute_0.arc)[0] = midpoint;
        attribute_0.previous = &attribute_1;
        attribute_0.previous_connection_type = direction_1;
    }
    else if (direction_0 == RIGHT)
    {
        (*attribute_0.arc)[3] = midpoint;
        attribute_0.next = &attribute_1;
        attribute_0.next_connection_type = direction_1;
    }

    if (direction_1 == LEFT)
    {
        (*attribute_1.arc)[0] = midpoint;
        attribute_1.previous = &attribute_0;
        attribute_1.previous_connection_type = direction_0;
    }
    else if (direction_1 == RIGHT)
    {
        (*attribute_1.arc)[3] = midpoint;
        attribute_1.next = &attribute_0;
        attribute_1.next_connection_type = direction_0;
    }

    if(!_attributes[index_0].arc->UpdateVertexBufferObjectsOfData() || !_attributes[index_1].arc->UpdateVertexBufferObjectsOfData())
        throw Exception("Could not update VBO of merged arc!");

    _attributes[index_0].image = _attributes[index_0].arc->GenerateImage(2, 200);
    _attributes[index_1].image = _attributes[index_1].arc->GenerateImage(2, 200);
    if (!_attributes[index_0].image || !_attributes[index_1].image)
        throw Exception("Could not generate image of arc!");

    if (!_attributes[index_0].image->UpdateVertexBufferObjects(1) || !_attributes[index_1].image->UpdateVertexBufferObjects(1))
        throw Exception("Could not update VBO of merged arc image!");

    return GL_TRUE;
}

GLuint FOAHCompositeArc::getAttributeIndex(ArcAttributes* attribute){
    for(GLuint i = 0; i < getArcCount(); ++i){
        if(&_attributes[i] == attribute){
            return i;
        }
    }
    return -1;
}

GLboolean innit(RowMatrix<GLuint> rm,GLuint e){
    for(GLuint i = 0; i < rm.GetColumnCount(); ++i){
        if(rm[i] == e){
            return GL_TRUE;
        }
    }

    return GL_FALSE;
}

GLvoid FOAHCompositeArc::getAllNeighbours(GLuint index, RowMatrix<GLuint>& neighbours){
    if(index >= getArcCount()){
        return;
    }

    neighbours.ResizeColumns(neighbours.GetColumnCount() + 1);
    neighbours[neighbours.GetColumnCount() - 1] = index;
    GLuint tempIndex;
    if(_attributes[index].next){
        tempIndex = getAttributeIndex(_attributes[index].next);
        if(!innit(neighbours, tempIndex))
            getAllNeighbours(getAttributeIndex(_attributes[index].next), neighbours);
    }

    if(_attributes[index].previous && _attributes[index].previous != _attributes[index].next){
        tempIndex = getAttributeIndex(_attributes[index].previous);
        if(!innit(neighbours, tempIndex))
            getAllNeighbours(getAttributeIndex(_attributes[index].previous), neighbours);
    }
}

GLvoid FOAHCompositeArc::pullArc(GLuint index, GLuint direction){
    RowMatrix<GLuint> neighbours(0);
    getAllNeighbours(index, neighbours);
    cout << neighbours << endl;
    for(GLuint i = 0; i < neighbours.GetColumnCount(); ++i){
        _attributes.at(neighbours[i]).pull(direction);
    }
}

GLvoid FOAHCompositeArc::pushArc(GLuint index, GLuint direction){
    RowMatrix<GLuint> neighbours(0);
    getAllNeighbours(index, neighbours);
    cout << neighbours << endl;
    for(GLuint i = 0; i < neighbours.GetColumnCount(); ++i){
        _attributes.at(neighbours[i]).push(direction);
    }
}

FOAHCompositeArc::~FOAHCompositeArc()
{
    for(auto& arcAttr : _attributes){
        arcAttr.image->DeleteVertexBufferObjects();
        arcAttr.arc->DeleteVertexBufferObjectsOfData();
    }
    _attributes.clear();
}
