/**
 * @file Vector3d.cpp
 * @brief 3-D Cartesian vectors
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 11 November 2014\n
 * Last modified on 8 October 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <Vector3d.h>

#include <utils.h>

#include <cmath>

//-----------------------------------------------------------------------------

const double Vector3d::BIG = 1.0e100;
const double Vector3d::SMALL = 1.0 / Vector3d::BIG;
const double Vector3d::ZERO = 0.0;
    
//-----------------------------------------------------------------------------

Vector3d::Vector3d(): x(0.0), y(0.0), z(0.0) {}

//-----------------------------------------------------------------------------

Vector3d::Vector3d(const double xin, const double yin, const double zin):
    x(xin), y(yin), z(zin) {}

//-----------------------------------------------------------------------------

Vector3d::Vector3d(const double theta, const double phi):
    x(sin(theta)*cos(phi)), y(sin(theta)*sin(phi)), z(cos(theta)) {}

//-----------------------------------------------------------------------------

void Vector3d::setx(const double xin)
{
    x = xin;
}

//-----------------------------------------------------------------------------

double Vector3d::getx() const
{
    return x;
}

//-----------------------------------------------------------------------------

void Vector3d::sety(const double yin)
{
    y = yin;
}

//-----------------------------------------------------------------------------

double Vector3d::gety() const
{
    return y;
}

//-----------------------------------------------------------------------------

void Vector3d::setz(const double zin)
{
    z = zin;
}

//-----------------------------------------------------------------------------

double Vector3d::getz() const
{
    return z;
}

//-----------------------------------------------------------------------------

void Vector3d::set0()
{
    x = y = z = 0.0;
}

//-----------------------------------------------------------------------------

double Vector3d::norm() const
{
    return sqrt(x*x + y*y + z*z);
}

//-----------------------------------------------------------------------------

double Vector3d::abs_diff(const Vector3d &v) const
{
    const double a = x - v.x;
    const double b = y - v.y;
    const double c = z - v.z;
    return sqrt(a*a + b*b + c*c);
}

//-----------------------------------------------------------------------------

std::string Vector3d::to_string() const
{
    return utils::double_to_string(x) +
           utils::double_to_string(y) +
           utils::double_to_string(z);
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::operator + () const
{
    return *this;
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::operator - () const
{
    return Vector3d(-x, -y, -z);
}

//-----------------------------------------------------------------------------

Vector3d & Vector3d::operator += (const Vector3d &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

//-----------------------------------------------------------------------------

Vector3d & Vector3d::operator -= (const Vector3d &v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::operator + (const Vector3d &v) const
{
    return Vector3d(x + v.x, y + v.y, z + v.z);
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::operator - (const Vector3d &v) const
{
    return Vector3d(x - v.x, y - v.y, z - v.z);
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::operator * (const double f) const
{
    return Vector3d(x*f, y*f, z*f);
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::operator * (const float f) const
{
    return *this * static_cast<double>(f);
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::operator * (const int f) const
{
    return *this * static_cast<double>(f);
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::operator * (const size_t f) const
{
    return *this * static_cast<double>(f);
}

//-----------------------------------------------------------------------------

Vector3d & Vector3d::normalize()
{
    const double f = norm();
    if (fabs(f) < SMALL) return *this;
    *this /= f;
    return *this;
}

//-----------------------------------------------------------------------------

Vector3d & Vector3d::reverse()
{
    x = -x;
    y = -y;
    z = -z;
    return *this;
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::unit() const
{
    Vector3d v(*this);
    return v.normalize();
}

//-----------------------------------------------------------------------------

double Vector3d::operator * (const Vector3d &v) const
{
    return x * v.x  +  y * v.y  +  z * v.z;
}

//-----------------------------------------------------------------------------

Vector3d & Vector3d::operator %= (const Vector3d &v)
{
    const Vector3d w(*this);
    x = w.y * v.z  -  v.y * w.z;
    y = w.z * v.x  -  v.z * w.x;
    z = w.x * v.y  -  v.x * w.y;
    return *this;
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::operator % (const Vector3d &v) const
{
    return Vector3d(y * v.z  -  v.y * z,
                    z * v.x  -  v.z * x,
                    x * v.y  -  v.x * y);
}

//-----------------------------------------------------------------------------

double Vector3d::cos_angle(const Vector3d &v) const
{
    const double tnorm = norm();
    const double vnorm = v.norm();
    if (fabs(tnorm) < SMALL || fabs(vnorm) < SMALL) return -4.0;
    return (*this * v) / (tnorm * vnorm);
}

//-----------------------------------------------------------------------------

double Vector3d::angle_rad(const Vector3d &v) const
{
    const double cosangle = cos_angle(v);
    if (cosangle < -2.0) return BIG;
    return acos(cosangle);
}

//-----------------------------------------------------------------------------

double Vector3d::distance(const Vector3d &v) const
{
    const Vector3d w = *this - v;
    return w.norm();
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::right_normal() const
{
    Vector3d w(y, -x, 0.0);
    return w.normalize();
}

//-----------------------------------------------------------------------------

int Vector3d::get_turn(const Vector3d &tail, const Vector3d &head) const
{   // pmh_2014_1125
    const Vector3d w =  head - tail;
    const Vector3d v = *this - tail;
    const double wvz = w.x * v.y  -  w.y * v.x; // z-component of (w x v)
    return utils::sign_eqt(wvz, SMALL); // negative for clockwise turn, etc.
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::parallel_to(const Vector3d &v) const // |v| != 0
{
    Vector3d e(v.unit());
    return e * (*this * e);
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::perpendicular_to(const Vector3d &v) const // |v| != 0
{
    return *this - parallel_to(v);
}

//-----------------------------------------------------------------------------

bool Vector3d::is_between(const Vector3d &tail, const Vector3d &head) const
{   // pmh_2015_0508, page 5; amended in pmh_2019_1031
    return (x - tail.x) * (x - head.x)  <=  ZERO   &&
           (y - tail.y) * (y - head.y)  <=  ZERO   &&
           (z - tail.z) * (z - head.z)  <=  ZERO;
}

//-----------------------------------------------------------------------------

Vector3d Vector3d::get_rz() const
{
    return Vector3d(sqrt(x*x + y*y), z, 0.0);
}

//-----------------------------------------------------------------------------

std::ostream & operator << (std::ostream &ost, const Vector3d &o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

Vector3d linear_Vector3d_fit(const double f,
                             const Vector3d &a, const Vector3d &b)
{
    double d = f / (a-b).norm();
    return (1.0-d) * a  +  d * b;
}

//-----------------------------------------------------------------------------

//  end Vector3d.cpp
