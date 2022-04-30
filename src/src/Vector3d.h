#ifndef LANL_ASC_PEM_VECTOR3D_H_
#define LANL_ASC_PEM_VECTOR3D_H_

/**
 * @file
 * @brief 3-D Cartesian vectors
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 11 November 2014\n
 * Last modified on 20 April 2022
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <cmath>
#include <iostream>
#include <string>

//-----------------------------------------------------------------------------

/// 3-D Cartesian vectors
class Vector3d
{
public:

    /// Default constructor
    Vector3d();

    /**
     * @brief Parametrized constructor (Cartesian input)
     * @param[in] xin Cartesian component x
     * @param[in] yin Cartesian component y
     * @param[in] zin Cartesian component z
     */
    Vector3d(const double xin, const double yin, const double zin);

    /**
     * @brief Parametrized constructor for a unit vector (spherical input)
     * @param[in] theta Polar angle (radians)
     * @param[in] phi Azimuthal angle (radians)
     */
    Vector3d(const double theta, const double phi); // build a unit vector

    /**
     * @brief Setter for Cartesian component x (Vector3d::x)
     * @param[in] xin Cartesian component x
     */
    void setx(const double xin);

    /**
     * @brief Getter for Cartesian component x (Vector3d::x)
     * @return Cartesian component x
     */
    double getx() const;

    /**
     * @brief Setter for Cartesian component y (Vector3d::y)
     * @param[in] yin Cartesian component y
     */
    void sety(const double yin);

    /**
     * @brief Getter for Cartesian component y (Vector3d::y)
     * @return Cartesian component y
     */
    double gety() const;

    /**
     * @brief Setter for Cartesian component z (Vector3d::z)
     * @param[in] zin Cartesian component z
     */
    void setz(const double zin);

    /**
     * @brief Getter for Cartesian component z (Vector3d::z)
     * @return Cartesian component z
     */
    double getz() const;

    /** @brief Set *this vector to null */
    void set0();

    /**
     * @brief Getter for proxy for Infinity (Vector3d::BIG)
     * @return Proxy for Infinity
     */
    static double get_big() {return BIG;};

    /**
     * @brief Getter for proxy for Zero (Vector3d::SMALL)
     * @return Proxy for Zero
     */
    static double get_small() {return SMALL;};

    /**
     * @brief Vector norm
     * @return \f$ v = |\vec{v}| \f$
     */
    double norm() const;

    /**
     * @brief Absolute difference between two vectors
     * @param[in] v Vector3d
     * @return \f$ |\vec{t}-\vec{v}| \f$
     */
    double abs_diff(const Vector3d &v) const;

    /**
     * @brief String representation of a Vector3d object
     * @return String representation of *this
     */
    std::string to_string() const;

    /**
     * @brief Unary plus
     * @return \f$+\vec{v}\f$
     */
    Vector3d operator + () const;

    /**
     * @brief Unary minus
     * @return \f$-\vec{v}\f$
     */
    Vector3d operator - () const;

    /**
     * @brief Adds to a vector
     * @param[in] v Vector3d
     * @return \f$\vec{t}\rightarrow\vec{t}+\vec{v}\f$
     */
    Vector3d & operator += (const Vector3d &v);

    /**
     * @brief Subtracts from a vector
     * @param[in] v Vector3d
     * @return \f$\vec{t}\rightarrow\vec{t}-\vec{v}\f$
     */
    Vector3d & operator -= (const Vector3d &v);

    /**
     * @brief Vector addition
     * @param[in] v Vector3d
     * @return \f$\vec{t}+\vec{v}\f$
     */
    Vector3d operator + (const Vector3d &v) const;

    /**
     * @brief Vector subtraction
     * @param[in] v Vector3d
     * @return \f$\vec{t}-\vec{v}\f$
     */
    Vector3d operator - (const Vector3d &v) const;

    /**
     * @brief Multiplies a vector by a scalar g
     * @param[in] g Scalar
     * @return \f$\vec{t}\rightarrow\vec{t}\;g\f$
     */
    template<typename T>
    Vector3d operator *= (const T g)
    {
        double f = static_cast<double>(g);
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }

    /**
     * @brief Divides a vector by a scalar g
     * @param[in] g Scalar
     * @return \f$\vec{t}\rightarrow\vec{t}\;/\;g\f$,
     *         \f$\infty\f$ if \f$g=0\f$
     */
    template<typename T>
    Vector3d operator /= (const T g)
    {
        double f = static_cast<double>(g);
        if (fabs(f) < SMALL)
            x = y = z = BIG;
        else
        {
            x /= f;
            y /= f;
            z /= f;
        }
        return *this;
    }

    /**
     * @brief Multiplication of a vector by a scalar f
     * @param[in] f Scalar
     * @return \f$\vec{t}\;f\f$
     */
    Vector3d operator * (const double f) const;

    /**
     * @brief Multiplication of a vector by a scalar f
     * @param[in] f Scalar
     * @return \f$\vec{t}\;f\f$
     */
    Vector3d operator * (const float f) const;

    /**
     * @brief Multiplication of a vector by a scalar f
     * @param[in] f Scalar
     * @return \f$\vec{t}\;f\f$
     */
    Vector3d operator * (const int f) const;

    /**
     * @brief Multiplication of a vector by a scalar f
     * @param[in] f Scalar
     * @return \f$\vec{t}\;f\f$
     */
    Vector3d operator * (const size_t f) const;

    /**
     * @brief Division of a vector by a scalar g
     * @param[in] g Scalar
     * @return \f$\vec{t}\;/\;g\f$,
     *         \f$\infty\f$ if \f$g=0\f$
     */
    template<typename T>
    Vector3d operator / (const T g) const
    {
        double f = static_cast<double>(g);
        if (fabs(f) < SMALL)
            return Vector3d(BIG, BIG, BIG);
        else
            return Vector3d(x/f, y/f, z/f);
    }
    
    /**
     * @brief Make vector unit length, maintain its direction
     * @return \f$\hat{t}=\vec{t}/t\f$, null vector remains unchanged
     */
    Vector3d & normalize();

    /**
     * @brief Flip vector direction, maintain its length
     * @return \f$\vec{t}\rightarrow -\vec{t}\f$
     */
    Vector3d & reverse();

    /**
     * @brief Unit vector in the same direction as *this
     * @return \f$\hat{t}=\vec{t}/t\f$, or the null vector
     */
    Vector3d unit() const;

    /**
     * @brief Scalar product of two vectors
     * @param[in] v Vector3d
     * @return \f$\vec{t}\bullet\vec{v}\f$
     */
    double operator * (const Vector3d &v) const;

    /**
     * @brief Vector multiplication
     * @param[in] v Vector3d
     * @return \f$\vec{t}\rightarrow\vec{t}\times\vec{v}\f$
     */
    Vector3d & operator %= (const Vector3d &v);

    /**
     * @brief Vector product of two vectors
     * @param[in] v Vector3d
     * @return \f$\vec{t}\times\vec{v}\f$
     */
    Vector3d operator % (const Vector3d &v) const;

    /**
     * @brief Cosine of the angle between two vectors
     * @param[in] v Vector3d
     * @return \f$\hat{t}\bullet\hat{v}\f$, or -4 if one of the vectors is null
     */
    double cos_angle(const Vector3d &v) const;

    /**
     * @brief The (smaller) angle between two vectors, in radians
     * @param[in] v Vector3d
     * @return \f$\arccos ( \hat{t}\bullet\hat{v} )\f$,
     *         or \f$\infty\f$ if one of the vectors is null
     */
    double angle_rad(const Vector3d &v) const;

    /**
     * @brief Distance betwen two points
     * @param[in] v Vector3d
     * @return \f$ |\vec{t}-\vec{v}| \f$
     */
    double distance(const Vector3d &v) const;

    /**
     * @brief Unit vector turned clockwise in 2-D (z-component is assumed = 0)
     * @return \f$\vec{t}\f$ turned clockwise and normalized,
     *         null vector remains unchanged
     */
    Vector3d right_normal() const;

    /**
     * @brief Relative orientation of two 2-D vectors in their common plane,
     *        see pmh_2014_1125 (*this relative to head-tail)
     * @param[in] tail Vector3d
     * @param[in] head Vector3d
     * @return -1 for clockwise, 0 for parallel, +1 for counter-clockwise
     */
    int get_turn(const Vector3d &tail, const Vector3d &head) const;

    /**
     * @brief Component of *this vector along a non-null vector v
     * @param[in] v Vector3d
     * @return \f$\vec{v_{\parallel}}=(\vec{t}\bullet\hat{v})\;\hat{v}\f$
     */
    Vector3d parallel_to(const Vector3d &v) const; // |v| != 0

    /**
     * @brief Component of *this vector perpendicular to a non-null vector v
     * @param[in] v Vector3d
     * @return \f$\vec{v_{\perp}}=\vec{t}-\vec{v_{\parallel}}\f$
     */
    Vector3d perpendicular_to(const Vector3d &v) const; // |v| != 0

    /**
     * @brief Detects ordering of three co-linear points,
     *        see pmh_2015_0508, page 5 (*this relative to head and tail)
     * @param[in] tail Vector3d
     * @param[in] head Vector3d
     * @return true if *this is within [head, tail], false otherwise
     */
    bool is_between(const Vector3d &tail, const Vector3d &head) const;

    /**
     * @brief Convert *this to cylindrical RZ coordinates in the *this/z plane
     * @return \f$(\sqrt{x^2+y^2}\;,z\;,0)\f$
     */
    Vector3d get_rz() const;


private:

    /// Cartesian component x
    double x;

    /// Cartesian component y
    double y;

    /// Cartesian component z
    double z;

    /// Proxy for Infinity
    static const double BIG;

    /// Proxy for Zero
    static const double SMALL;

    /// Zero
    static const double ZERO;
};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of Vector3d to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o Vector3d object
 * @return Reference to output stream
 */
 std::ostream & operator << (std::ostream &ost, const Vector3d &o);

//-----------------------------------------------------------------------------

/**
 * @brief Multiplication of a vector by a scalar f
 * @param[in] f Scalar
 * @param[in] v Vector3d
 * @return \f$f\;\vec{t}\f$
 */
template<typename T>
Vector3d operator * (const T f, const Vector3d &v)
{
    return v * f;
}

//-----------------------------------------------------------------------------

/**
 * @brief Return a Vector3d on the line connecting two Vector3d objects
 * @param[in] f Signed distance from a toward b
 * @param[in] a First Vector3d (f = 0)
 * @param[in] b Second Vector3d (f = |a-b|)
 * @return Vector3d on the line connecting a and b at signed distance f from a
 */
Vector3d linear_Vector3d_fit(const double f,
                             const Vector3d &a, const Vector3d &b);

//-----------------------------------------------------------------------------

/**
 * @brief Return whether two lines in 3D intersect or not
 * @param[in] p Point on the first line
 * @param[in] u First line's direction vector
 * @param[in] q Point on the second line
 * @param[in] v Second line's direction vector
 * @param[in] eqt Numerical tolerance ("zero")
 * @return true/false
 */
bool lines_intersect(const Vector3d &p, const Vector3d &u,
                     const Vector3d &q, const Vector3d &v,
                     const double eqt);

//-----------------------------------------------------------------------------

/**
 * @brief Return the intersection of two lines (representing a Ray and a Cone)
 * @param[in] p Point on the first line (from Ray)
 * @param[in] u First line's direction vector (from Ray)
 * @param[in] a One point on the second line (from Cone)
 * @param[in] b Another point on the second line (from Cone)
 * @param[in] eqt Numerical tolerance ("zero")
 * @return first=true/false (i.e., found/not_found); second=intersection_point
 */
std::pair<bool, Vector3d>
lines_intersection(const Vector3d &p, const Vector3d &u,
                   const Vector3d &a, const Vector3d &b,
                   const double eqt);
//-----------------------------------------------------------------------------

#endif  // LANL_ASC_PEM_VECTOR3D_H_
