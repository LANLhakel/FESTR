/**
 * @file ArrDbl.cpp
 * @brief Array of doubles
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 3 December 2014\n
 * Last modified on 27 February 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <ArrDbl.h>

#include <utils.h>
#include <Vector3d.h>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <stdexcept>

//-----------------------------------------------------------------------------

ArrDbl::ArrDbl(): n(0), v() {}

//-----------------------------------------------------------------------------

ArrDbl::ArrDbl(const size_t nin): n(nin), v()
{
    v.assign(nin, 0.0);
}

//-----------------------------------------------------------------------------

void ArrDbl::clear()
{
    n = 0;
    v.clear();
}

//-----------------------------------------------------------------------------

size_t ArrDbl::size() const
{
    return n;
}

//-----------------------------------------------------------------------------

void ArrDbl::reserve(const size_t nin)
{
    v.reserve(nin);
}

//-----------------------------------------------------------------------------

void ArrDbl::push_back(const double x)
{
    ++n;
    v.push_back(x);
}

//-----------------------------------------------------------------------------

void ArrDbl::emplace_back(const double x)
{
    ++n;
    v.emplace_back(std::move(x));
}

//-----------------------------------------------------------------------------

double ArrDbl::at(const size_t i) const // rvalue
{
    return v.at(i);
}

//-----------------------------------------------------------------------------

double & ArrDbl::at(const size_t i) // lvalue
{
    return v.at(i);
}

//-----------------------------------------------------------------------------

double ArrDbl::operator [](const size_t i) const // rvalue
{
    return v[i];
}

//-----------------------------------------------------------------------------

double & ArrDbl::operator [](const size_t i) // lvalue
{
    return v[i];
}

//-----------------------------------------------------------------------------

double ArrDbl::abs_diff(const ArrDbl &o) const
{
    const size_t na = o.size();
    double d = fabs(static_cast<double>(n) - static_cast<double>(na));
    const size_t nmin = std::min(n, na);
    for (size_t i = 0; i < nmin; ++i) d += fabs(at(i) - o.at(i));
    return d;
}

//-----------------------------------------------------------------------------

std::string ArrDbl::to_string() const
{
    std::string s = "";
    for (size_t i = 0; i < n; ++i)
    {
        if (i > 0) s += "\n";
        s += utils::double_to_string(v.at(i));
    }
    return s;
}

//-----------------------------------------------------------------------------

void ArrDbl::to_file(const std::string &fname,
                     const std::string &header) const
{
    std::ofstream outfile(fname.c_str());
    outfile << header << "\n" << to_string();
    outfile.close();
    outfile.clear();
}

//-----------------------------------------------------------------------------

void ArrDbl::assign(const size_t nin, const double f)
{
    n = nin;
    v.assign(nin, f);
}

//-----------------------------------------------------------------------------

void ArrDbl::assign(const size_t nin, const float f)
{
    assign(nin, static_cast<double>(f));
}

//-----------------------------------------------------------------------------

void ArrDbl::assign(const size_t nin, const int f)
{
    assign(nin, static_cast<double>(f));
}

//-----------------------------------------------------------------------------

void ArrDbl::fill(const double f)
{
    v.assign(n, f);
}

//-----------------------------------------------------------------------------

void ArrDbl::fill(const float f)
{
    fill(static_cast<double>(f));
}

//-----------------------------------------------------------------------------

void ArrDbl::fill(const int f)
{
    fill(static_cast<double>(f));
}

//-----------------------------------------------------------------------------

const ArrDbl ArrDbl::operator + () const
{
    return *this;
}

//-----------------------------------------------------------------------------

const ArrDbl ArrDbl::operator - () const
{
    #include <ArrDblRVinit.inc>
    for (size_t i = 0; i < n; ++i) rv.v.at(i) = -at(i);
    return rv;
}

//-----------------------------------------------------------------------------

ArrDbl & ArrDbl::operator += (const ArrDbl &a)
{
    #include <ArrDblRangeCheck.inc>
    for (size_t i = 0; i < n; ++i) v.at(i) += a.at(i);
    return *this;
}

//-----------------------------------------------------------------------------

ArrDbl & ArrDbl::operator -= (const ArrDbl &a)
{
    #include <ArrDblRangeCheck.inc>
    for (size_t i = 0; i < n; ++i) v.at(i) -= a.at(i);
    return *this;
}

//-----------------------------------------------------------------------------

ArrDbl & ArrDbl::operator *= (const ArrDbl &a)
{
    #include <ArrDblRangeCheck.inc>
    for (size_t i = 0; i < n; ++i) v.at(i) *= a.at(i);

    return *this;
}

//-----------------------------------------------------------------------------

ArrDbl & ArrDbl::operator /= (const ArrDbl &a)
{
    const double SMALL = Vector3d::get_small();
    const double BIG = -Vector3d::get_big();

    #include <ArrDblRangeCheck.inc>
    for (size_t i = 0; i < n; ++i)
    {
        if (fabs(a.at(i)) < SMALL)
            v.at(i) = BIG;
        else
            v.at(i) /= a.at(i);
    }

    return *this;
}

//-----------------------------------------------------------------------------

const ArrDbl ArrDbl::operator + (const ArrDbl &a) const
{
    #include <ArrDblRVinit.inc>
    rv = *this;
    return rv += a;
}

//-----------------------------------------------------------------------------

const ArrDbl ArrDbl::operator - (const ArrDbl &a) const
{
    #include <ArrDblRVinit.inc>
    rv = *this;
    return rv -= a;
}

//-----------------------------------------------------------------------------

const ArrDbl ArrDbl::operator * (const ArrDbl &a) const
{
    #include <ArrDblRVinit.inc>
    rv = *this;
    return rv *= a;
}

//-----------------------------------------------------------------------------

const ArrDbl ArrDbl::operator / (const ArrDbl &a) const
{
    #include <ArrDblRVinit.inc>
    rv = *this;
    return rv /= a;
}

//-----------------------------------------------------------------------------

ArrDbl & ArrDbl::operator += (const double f)
{
    std::for_each(v.begin(), v.end(), [f](double &y){y += f;});
    return *this;
}

//-----------------------------------------------------------------------------

ArrDbl & ArrDbl::operator += (const float f)
{
    return *this += static_cast<double>(f);
}

//-----------------------------------------------------------------------------

ArrDbl & ArrDbl::operator += (const int f)
{
    return *this += static_cast<double>(f);
}

//-----------------------------------------------------------------------------

ArrDbl & ArrDbl::operator -= (const double f)
{
    std::for_each(v.begin(), v.end(), [f](double &y){y -= f;});
    return *this;
}

//-----------------------------------------------------------------------------

ArrDbl & ArrDbl::operator -= (const float f)
{
    return *this -= static_cast<double>(f);
}

//-----------------------------------------------------------------------------

ArrDbl & ArrDbl::operator -= (const int f)
{
    return *this -= static_cast<double>(f);
}

//-----------------------------------------------------------------------------

ArrDbl & ArrDbl::operator *= (const double f)
{
    std::for_each(v.begin(), v.end(), [f](double &y){y *= f;});
    return *this;
}

//-----------------------------------------------------------------------------

ArrDbl & ArrDbl::operator *= (const float f)
{
    return *this *= static_cast<double>(f);
}

//-----------------------------------------------------------------------------

ArrDbl & ArrDbl::operator *= (const int f)
{
    return *this *= static_cast<double>(f);
}

//-----------------------------------------------------------------------------

ArrDbl & ArrDbl::operator /= (const double f)
{
    if (fabs(f) < Vector3d::get_small())
    {
        const double BIG = -Vector3d::get_big();
        std::for_each(v.begin(), v.end(), [BIG](double &y){y = BIG;});
    }
    else
    {
        std::for_each(v.begin(), v.end(), [f](double &y){y /= f;});
    }

    return *this;
}

//-----------------------------------------------------------------------------

ArrDbl & ArrDbl::operator /= (const float f)
{
    return *this /= static_cast<double>(f);
}

//-----------------------------------------------------------------------------

ArrDbl & ArrDbl::operator /= (const int f)
{
    return *this /= static_cast<double>(f);
}

//-----------------------------------------------------------------------------

const ArrDbl ArrDbl::operator + (const double f) const
{
    #include <ArrDblRVinit.inc>
    rv = *this;
    return rv += f;
}

//-----------------------------------------------------------------------------

const ArrDbl ArrDbl::operator + (const float f) const
{
    return *this + static_cast<double>(f);
}

//-----------------------------------------------------------------------------

const ArrDbl ArrDbl::operator + (const int f) const
{
    return *this + static_cast<double>(f);
}

//-----------------------------------------------------------------------------

const ArrDbl ArrDbl::operator - (const double f) const
{
    #include <ArrDblRVinit.inc>
    rv = *this;
    return rv -= f;
}

//-----------------------------------------------------------------------------

const ArrDbl ArrDbl::operator - (const float f) const
{
    return *this - static_cast<double>(f);
}

//-----------------------------------------------------------------------------

const ArrDbl ArrDbl::operator - (const int f) const
{
    return *this - static_cast<double>(f);
}

//-----------------------------------------------------------------------------

const ArrDbl ArrDbl::operator * (const double f) const
{
    #include <ArrDblRVinit.inc>
    rv = *this;
    return rv *= f;
}

//-----------------------------------------------------------------------------

const ArrDbl ArrDbl::operator * (const float f) const
{
    return *this * static_cast<double>(f);
}

//-----------------------------------------------------------------------------

const ArrDbl ArrDbl::operator * (const int f) const
{
    return *this * static_cast<double>(f);
}

//-----------------------------------------------------------------------------

const ArrDbl ArrDbl::operator / (const double f) const
{
    #include <ArrDblRVinit.inc>
    rv = *this;
    return rv /= f;
}

//-----------------------------------------------------------------------------

const ArrDbl ArrDbl::operator / (const float f) const
{
    return *this / static_cast<double>(f);
}

//-----------------------------------------------------------------------------

const ArrDbl ArrDbl::operator / (const int f) const
{
    return *this / static_cast<double>(f);
}

//-----------------------------------------------------------------------------

const ArrDbl operator / (const double f, const ArrDbl &a)
{
    const size_t n = a.size();
    #include <ArrDblRVinit.inc>
    rv.assign(n, f);
    return rv / a;
}

//-----------------------------------------------------------------------------

std::ostream & operator << (std::ostream &ost, const ArrDbl &o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

const ArrDbl operator + (const double f, const ArrDbl &a)
{
    return a + f;
}

//-----------------------------------------------------------------------------

const ArrDbl operator + (const float f, const ArrDbl &a)
{
    return a + f;
}

//-----------------------------------------------------------------------------

const ArrDbl operator + (const int f, const ArrDbl &a)
{
    return a + f;
}

//-----------------------------------------------------------------------------

const ArrDbl operator - (const double f, const ArrDbl &a)
{
    return -(a - f);
}

//-----------------------------------------------------------------------------

const ArrDbl operator - (const float f, const ArrDbl &a)
{
    return -(a - f);
}

//-----------------------------------------------------------------------------

const ArrDbl operator - (const int f, const ArrDbl &a)
{
    return -(a - f);
}

//-----------------------------------------------------------------------------

const ArrDbl operator * (const double f, const ArrDbl &a)
{
    return a * f;
}

//-----------------------------------------------------------------------------

const ArrDbl operator * (const float f, const ArrDbl &a)
{
    return a * f;
}

//-----------------------------------------------------------------------------

const ArrDbl operator * (const int f, const ArrDbl &a)
{
    return a * f;
}

//-----------------------------------------------------------------------------

const ArrDbl operator / (const float f, const ArrDbl &a)
{
    return static_cast<double>(f) / a;
}

//-----------------------------------------------------------------------------

const ArrDbl operator / (const int f, const ArrDbl &a)
{
    return static_cast<double>(f) / a;
}

//-----------------------------------------------------------------------------

const ArrDbl log(const ArrDbl &a)
{
    const double SMALL = Vector3d::get_small();
    const double BIG = -Vector3d::get_big();
    const size_t n = a.size();
    ArrDbl rv(a);
    for (size_t i = 0; i < n; ++i)
    {
        if (utils::sign_eqt(a.at(i), SMALL) == 1)
            rv.at(i) = log(a.at(i));
        else
            rv.at(i) = BIG;
    }
    return rv;
}

//-----------------------------------------------------------------------------

const ArrDbl exp(const ArrDbl &a)
{
    const size_t n = a.size();
    ArrDbl rv(a);
    for (size_t i = 0; i < n; ++i) rv.at(i) = exp(a.at(i));
    return rv;
}

//-----------------------------------------------------------------------------

//  end ArrDbl.cpp
