#pragma once

#include <cmath>
#include <GL/glew.h>
#include <iostream>

namespace cagd
{
    //--------------------------------------
    // 3-dimensional homogeneous coordinates
    //--------------------------------------
    class HCoordinate3
    {
    protected:
        GLfloat _data[4]; // x, y, z, w;

    public:
        // default constructor
        HCoordinate3();

        // special constructor
        HCoordinate3(GLfloat x, GLfloat y, GLfloat z = 0.0, GLfloat w = 1.0);

        // homework: get components by value
        GLfloat operator[](GLuint rhs) const { return this->_data[rhs]; }
        GLfloat x() const { return this->_data[0]; }
        GLfloat y() const { return this->_data[1]; }
        GLfloat z() const { return this->_data[2]; }
        GLfloat w() const { return this->_data[3]; }

        // homework: get components by reference
        GLfloat& operator[](GLuint rhs){ return this->_data[rhs]; }
        GLfloat& x() { return this->_data[0]; }
        GLfloat& y() { return this->_data[1]; }
        GLfloat& z() { return this->_data[2]; }
        GLfloat& w() { return this->_data[3]; }

        // add
        const HCoordinate3 operator +(const HCoordinate3& rhs) const;

        // homework: add to this
        HCoordinate3& operator +=(const HCoordinate3& rhs);

        // homework: subtract
        const HCoordinate3 operator -(const HCoordinate3& rhs) const;

        // homework: subtract from this
        HCoordinate3& operator -=(const HCoordinate3& rhs);

        // homework: dot product
        GLfloat operator *(const HCoordinate3& rhs) const;

        // homework: cross product
        const HCoordinate3 operator ^(const HCoordinate3& rhs) const;

        // homework: cross product with this
        HCoordinate3& operator ^=(const HCoordinate3& rhs);

        // homework: multiplicate with scalar from right
        const HCoordinate3 operator *(GLfloat rhs) const;

        // homework: multiplicate this with a scalar
        HCoordinate3& operator *=(GLfloat rhs);

        // homework: divide with scalar
        const HCoordinate3 operator /(GLfloat rhs) const;

        // homework: divide this with a scalar
        HCoordinate3& operator /=(GLfloat rhs);

        // homework: length of vector represented by this homogeneous coordinate
        GLfloat length() const;

        // homework: normalize
        HCoordinate3& normalize();
    };

    // default constructor
    inline HCoordinate3::HCoordinate3()
    {
        _data[0] = _data[1] = _data[2] = 0.0;
        _data[3] = 1.0;
    }

    // special constructor
    inline HCoordinate3::HCoordinate3(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {
        _data[0] = x;
        _data[1] = y;
        _data[2] = z;
        _data[3] = w;
    }

    // add
    inline const HCoordinate3 HCoordinate3::operator +(const HCoordinate3& rhs) const
    {
        return HCoordinate3(
                rhs.w() * x() + w() * rhs.x(),
                rhs.w() * y() + w() * rhs.y(),
                rhs.w() * z() + w() * rhs.z(),
                w() * rhs.w());
    }

    // homework: add to this
    inline HCoordinate3& HCoordinate3::operator +=(const HCoordinate3& rhs)
    {
        this->_data[0] = _data[0] * rhs.w() + _data[3] * rhs.x();
        this->_data[1] = rhs.w() * _data[1] + _data[3] * rhs.y();
        this->_data[2] = rhs.w() * _data[2] + _data[3] * rhs.z();
        this->_data[3] = _data[3] * rhs.w();

        return *this;
    }

    // homework: subtract
    inline const HCoordinate3 HCoordinate3::operator -(const HCoordinate3& rhs) const
    {
        return HCoordinate3(
                rhs.w() * x() - w() * rhs.x(),
                rhs.w() * y() - w() * rhs.y(),
                rhs.w() * z() - w() * rhs.z(),
                w() * rhs.w());
    }

    // homework: subtract from this
    inline HCoordinate3& HCoordinate3::operator -=(const HCoordinate3& rhs)
    {   this->_data[0] = _data[0] * rhs.w() - _data[3] * rhs.x();
        this->_data[1] = rhs.w() * _data[1] - _data[3] * rhs.y();
        this->_data[2] = rhs.w() * _data[2] - _data[3] * rhs.z();
        this->_data[3] = _data[3] * rhs.w();

        return *this;
    }

    // homework: dot product
    inline GLfloat HCoordinate3::operator *(const HCoordinate3& rhs) const{
        GLfloat newW = _data[3] * rhs.w();
        GLfloat res = (_data[0] * rhs.x()) / newW +
                      (_data[1] * rhs.y()) / newW +
                      (_data[2] * rhs.z()) / newW;

        return res;
    }

    // homework: cross product
    inline const HCoordinate3 HCoordinate3::operator ^(const HCoordinate3& rhs) const{
        return HCoordinate3(
                    _data[1] * rhs.z() - _data[2] * rhs.y(),
                    _data[2] * rhs.x() - _data[0] * rhs.z(),
                    _data[0] * rhs.y() - _data[1] * rhs.x(),
                    _data[3] * rhs.w()
                    );
    }

    // homework: cross product with this
    inline HCoordinate3& HCoordinate3::operator ^=(const HCoordinate3& rhs){
        GLfloat xtemp = _data[1] * rhs.z() - _data[2] * rhs.y();
        GLfloat ytemp = _data[2] * rhs.x() - _data[0] * rhs.z();

        _data[2] = _data[0] * rhs.y() - _data[1] * rhs.x();
        _data[3] = _data[3] * rhs.w();

        _data[0] = xtemp;
        _data[1] = ytemp;

        return *this;
    }

    // homework: multiplicate with scalar from right
    inline const HCoordinate3 HCoordinate3::operator *(GLfloat rhs) const{
        return HCoordinate3(_data[0] * rhs, _data[1] * rhs, _data[2] * rhs, _data[3]);
    }

    // homework: multiplicate this with a scalar
    inline HCoordinate3& HCoordinate3::operator *=(GLfloat rhs){
        _data[0] *= rhs;
        _data[1] *= rhs;
        _data[2] *= rhs;

        return *this;
    }

    // homework: divide with scalar
    inline const HCoordinate3 HCoordinate3::operator /(GLfloat rhs) const{
        return HCoordinate3(_data[0], _data[1], _data[2], _data[3] * rhs);
    }

    // homework: divide this with a scalar
    inline HCoordinate3& HCoordinate3::operator /=(GLfloat rhs){
        _data[3] *= rhs;

        return *this;
    }

    // homework: length of vector represented by this homogeneous coordinate
    inline GLfloat HCoordinate3::length() const{
        return sqrt((*this) * (*this));
    }

    // homework: normalize
    inline HCoordinate3& HCoordinate3::normalize(){
        GLfloat len = length();

        if(len && len != 1.0){
            *this /= len;
        }

        return *this;
    }

    // homework: scale from left with a scalar
    inline const HCoordinate3 operator *(GLfloat lhs, const HCoordinate3& rhs){
        return HCoordinate3(lhs*rhs.x(), lhs*rhs.y(), lhs*rhs.z(), rhs.w());
    }

    // homework: output to stream
    inline std::ostream& operator <<(std::ostream& lhs, const HCoordinate3& rhs){
        lhs << rhs.x() << " " << rhs.y() << " " << rhs.z() << " " << rhs.w() << std::endl;
                return lhs;
    }

    // homework: input from stream
    inline std::istream& operator >>(std::istream& lhs, HCoordinate3& rhs){
        lhs >> rhs.x() >> rhs.y() >> rhs.z() >> rhs.w();
        return lhs;
    }
}
