#include "FOAHCompositeArc.h"
#include "Core/Exceptions.h"
#include <GL/glu.h>

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
    for(auto& arcAttr : _attributes){
        if(arcAttr.image){
            glColor3f(arcAttr.color->r(), arcAttr.color->g(), arcAttr.color->b());
            arcAttr.image->RenderDerivatives(order, render_mode);
            arcAttr.arc->RenderData(render_mode);
        } else{
            return GL_FALSE;
        }
    }

    return GL_TRUE;
}

GLboolean FOAHCompositeArc::RenderSelectedArc(GLuint index, GLuint order, GLenum render_mode) const
{
    if(_attributes.at(index).image){
        glColor3f(_attributes.at(index).color->r(), _attributes.at(index).color->g(), _attributes.at(index).color->b());
        _attributes.at(index).image->RenderDerivatives(order, render_mode);
        _attributes.at(index).arc->RenderData(render_mode);
    }
    else{
        return GL_FALSE;
    }

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
