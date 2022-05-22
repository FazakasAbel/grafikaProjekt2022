#include <cmath>
#include "TestFunctions.h"
#include "../Core/Constants.h"

using namespace cagd;
using namespace std;

GLdouble spiral_on_cone::u_min = 0;
GLdouble spiral_on_cone::u_max = TWO_PI;

DCoordinate3 spiral_on_cone::d0(GLdouble u)
{
    return DCoordinate3(u * cos(u), u * sin(u), u);
}

DCoordinate3 spiral_on_cone::d1(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(c - u * s, s + u * c, 1.0);
}

DCoordinate3 spiral_on_cone::d2(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    return DCoordinate3(-2.0 * s - u * c, 2.0 * c - u * s, 0);
}

GLdouble torus_curve::u_max = 3 * TWO_PI;
GLdouble torus_curve::u_min = 0.0;

GLdouble torus_curve::v(GLdouble u){
    return 2 * u / 3;
}

DCoordinate3 torus_curve::d0(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    GLdouble a = (2 + cos((2 * u)/3));
    return DCoordinate3(a * c, a * s, sin((2 * u)/3));
}

DCoordinate3 torus_curve::d1(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    GLdouble a = cos((2 * u)/3) + 2, b = (2 * sin((2 * u)/3)) / 3;
    return DCoordinate3(-a * s - b * c, a * c - b * s, (2 * cos((2 * u)/3)) / 3);
}

DCoordinate3 torus_curve::d2(GLdouble u)
{
    GLdouble c = cos(u), s = sin(u);
    GLdouble a = sin((2 * u)/3), b = cos((2 * u)/3);
    return DCoordinate3((12 * a * s + (-13 * b - 18) * c) / 9, ((13 * b + 18) * s + 12 * a * c) / 9, (-4 * a) / 9);
}

GLdouble rose::u_min = 0.0;
GLdouble rose::u_max = TWO_PI;
GLdouble rose::k = 2.0;

DCoordinate3 rose::d0(GLdouble u)
{
    GLdouble ck = cos(k * u);
    return DCoordinate3(ck * cos(u), ck*sin(u), u);
}

DCoordinate3 rose::d1(GLdouble u)
{
    GLdouble ck = cos(k * u);
    GLdouble sk = sin(k * u);
    return DCoordinate3(-k *sk * cos(u) - ck * sin(u), -k*sk*sin(u) + ck * cos(u), 1.0);
}

DCoordinate3 rose::d2(GLdouble u)
{
    GLdouble ck = cos(k * u);
    GLdouble sk = sin(k * u);
    return DCoordinate3(-k * k * ck * cos(u) - k * sk * sin(u)- (-k*sk * sin(u) + ck * cos(u)),
                        -k * k * ck * sin(u) - k * sk * cos(u) - k * sk * cos(u) - ck * sin(u),
                        0.0);
}

GLdouble hypotrochoid::u_min = 0.0;
GLdouble hypotrochoid::u_max = 3.0*TWO_PI;
GLdouble hypotrochoid::r = 3.0;
GLdouble hypotrochoid::R = 5.0;
GLdouble hypotrochoid::d = 5.0;


DCoordinate3 hypotrochoid::d0(GLdouble u)
{
    GLdouble Rmr = R-r;
    GLdouble c = cos((Rmr/r)*u);
    GLdouble s = sin((Rmr/r)*u);
    return DCoordinate3(Rmr*cos(u) + d*c, Rmr*sin(u) - d*s, u);
}

DCoordinate3 hypotrochoid::d1(GLdouble u)
{
    GLdouble Rmr = R-r;
    GLdouble c = cos((Rmr/r)*u);
    GLdouble s = sin((Rmr/r)*u);
    return DCoordinate3(Rmr*(-sin(u)) - d*(Rmr/r)*s, Rmr*cos(u) - d*(Rmr/r)*c, 1.0);
}

DCoordinate3 hypotrochoid::d2(GLdouble u)
{
    GLdouble Rmr = R-r;
    GLdouble c = cos((Rmr/r)*u);
    GLdouble s = sin((Rmr/r)*u);
    return DCoordinate3(Rmr*(-cos(u)) - d*((Rmr*Rmr)/(r*r))*c, Rmr*(-sin(u)) + d*((Rmr*Rmr)/(r*r))*s, 0.0);
}

GLdouble circle::u_max = TWO_PI;
GLdouble circle::u_min = 0.0;

GLdouble circle::v(GLdouble u){
    return u;
}

DCoordinate3 circle::d0(GLdouble u)
{
    return DCoordinate3(cos(u), sin(u), u);
}

DCoordinate3 circle::d1(GLdouble u)
{
    return DCoordinate3(-sin(u), cos(u), 1.0);
}

DCoordinate3 circle::d2(GLdouble u)
{
    return DCoordinate3(-cos(u), -sin(u), 0.0);
}

GLdouble sphere_curve::u_max = TWO_PI;
GLdouble sphere_curve::u_min = 0.0;

GLdouble sphere_curve::v(GLdouble u){
    return (2 * u);
}

DCoordinate3 sphere_curve::d0(GLdouble u)
{
    return DCoordinate3(sin(u) * cos(2 * u), sin(u) * sin(2 * u), cos(u));
}

DCoordinate3 sphere_curve::d1(GLdouble u)
{
    return DCoordinate3(sin(u) * -2 * sin(2 * u) + cos(u) * cos(2 * u),
                        cos(u) * sin(2 * u) + sin(u) * 2 * cos(2 * u),
                        -sin(u));
}

DCoordinate3 sphere_curve::d2(GLdouble u)
{
    return DCoordinate3(cos(u) * -2 * sin(2 * u) + sin(u) * -4 * cos(2 * u) - sin(u) * cos(2 * u) - cos(u) * 2 * sin(2 * u),
                        -sin(u) * sin(2 * u) + cos(u) * 2 * cos(2 * u) + cos(u) * 2 * cos(2 * u) - sin(u) * 4 * cos(2 * u),
                        -sin(u));
}

GLdouble cylinder_curve::u_max = TWO_PI;
GLdouble cylinder_curve::u_min = 0.0;
GLdouble cylinder_curve::r = 4;

DCoordinate3 cylinder_curve::d0(GLdouble u)
{
     return DCoordinate3(r * cos(u), r * sin(u), 1);
}

DCoordinate3 cylinder_curve::d1(GLdouble u)
{
    return DCoordinate3(-r * sin(u),
                        r * cos(u),
                        0);
}

DCoordinate3 cylinder_curve::d2(GLdouble u)
{
    return DCoordinate3(-r * cos(u),
                        -r * sin(u),
                        0);
}

//Torus Surface
GLdouble surface_torus::u_min = 0;
GLdouble surface_torus::u_max = TWO_PI;
GLdouble surface_torus::v_min = 0;
GLdouble surface_torus::v_max = TWO_PI;

DCoordinate3 surface_torus::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3((2 + cos(v)) * cos(u),(2 + cos(v)) * sin(u), sin(v));
}

DCoordinate3 surface_torus::d10(GLdouble u, GLdouble v)
{
     return DCoordinate3(-(2 + cos(v)) * sin(u), (2 + cos(v)) * cos(u), 0.0);
}

DCoordinate3 surface_torus::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(-sin(v) * cos(u), -sin(v) * sin(u), cos(v));
}


//Sphere surface
GLdouble surface_sphere::v_min = 0;
GLdouble surface_sphere::v_max = TWO_PI;
GLdouble surface_sphere::u_min = EPS;
GLdouble surface_sphere::u_max = PI-EPS;

DCoordinate3 surface_sphere::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(sin(u)*cos(v), sin(u) * sin(v), cos(u));
}
DCoordinate3 surface_sphere::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(cos(u)*cos(v), cos(u) * sin(v), -sin(u));
}
DCoordinate3 surface_sphere::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(-sin(u)*sin(v), sin(u) * cos(v), 0.0);
}

// Helicoid
GLdouble helicoid::u_min = 0;
GLdouble helicoid::u_max = TWO_PI;
GLdouble helicoid::v_min = 0;
GLdouble helicoid::v_max = TWO_PI;

DCoordinate3 helicoid::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(u * cos(v), u * sin(v), v);
}

DCoordinate3 helicoid::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(cos(v), sin(v), 0.0f);
}

DCoordinate3 helicoid::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(-u * sin(v), u * cos(v), 1.0f);
}


// Cone
GLdouble cone::u_min = 0;
GLdouble cone::u_max = TWO_PI;
GLdouble cone::v_min = 0;
GLdouble cone::v_max = TWO_PI;

DCoordinate3 cone::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(u * cos(v), u * sin(v), u);
}

DCoordinate3 cone::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(cos(v), sin(v), 1.0f);
}

DCoordinate3 cone::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(-u * sin(v), u * cos(v), 0.0f);
}

// YoYo alaku cucc
GLdouble own::u_min = -TWO_PI;
GLdouble own::u_max = TWO_PI;
GLdouble own::v_min = 0;
GLdouble own::v_max = TWO_PI;

DCoordinate3 own::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(sqrt(1 + u*u) * cos(v), sqrt(1 + u*u) * sin(v), u);
}

DCoordinate3 own::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3((cos(v) * u) / sqrt(1 + u*u), (sin(v) * u) / sqrt(1 + u*u), 1.0f);
}

DCoordinate3 own::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(-sqrt(1 + u*u) * sin(v), sqrt(1 + u*u) * cos(v), 0.0f);
}

// Cylinder Surface
GLdouble surface_cylinder::u_min = 0;
GLdouble surface_cylinder::u_max = TWO_PI;
GLdouble surface_cylinder::v_min = 0;
GLdouble surface_cylinder::v_max = TWO_PI;

DCoordinate3 surface_cylinder::d00(GLdouble u, GLdouble v)
{
    return DCoordinate3(4 * cos(u), 4*sin(u), v);
}
DCoordinate3 surface_cylinder::d10(GLdouble u, GLdouble v)
{
    return DCoordinate3(-4 * sin(u), 4*cos(u), 0);
}
DCoordinate3 surface_cylinder::d01(GLdouble u, GLdouble v)
{
    return DCoordinate3(0, 0, 1);
}
