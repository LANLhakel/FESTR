#ifndef SPHERE_H
#define SPHERE_H

/**
 * @file Sphere.h
 * @brief Spherical shells (derived from class Face)
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 21 November 2014\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include "Face.h"

//-----------------------------------------------------------------------------

/// Spherical shells (derived from class Face)
class Sphere : public Face
{
private:

    /**
     * @brief Signed radius (cm) relative to (inherited) center
     *        (r > 0 for outer Zone surface; r < 0 for inner Zone surface)
     */
    double r;

    /**
     * @brief Signed surface velocity (cm/s) relative to (inherited) center
     *        (v > 0 outward; v < 0 inward)
     */
    double v;

public:

    /// Default constructor
    Sphere(void);

    /**
     * @brief Parametrized constructor (leaves Face::node, Face::nbr empty)
     * @param[in] my_zone_in Initializes FaceID::my_zone
     * @param[in] my_id_in Initializes FaceID::my_id
     */
    Sphere(const size_t my_zone_in, const short int my_id_in);

    /**
     * @brief Parametrized constructor (leaves Face::node, Face::nbr empty)
     * @param[in] my_zone_in Initializes FaceID::my_zone
     * @param[in] my_id_in Initializes FaceID::my_id
     * @param[in] rin Initializes Sphere::r
     */
    Sphere(const size_t my_zone_in, const short int my_id_in,
           const double rin);

    /**
     * @brief Parametrized constructor (leaves Face::node, Face::nbr empty)
     * @param[in] my_zone_in Initializes FaceID::my_zone
     * @param[in] my_id_in Initializes FaceID::my_id
     * @param[in] rin Initializes Sphere::r
     * @param[in] vin Initializes Sphere::v
     */
    Sphere(const size_t my_zone_in, const short int my_id_in,
           const double rin, const double vin);

    /**
     * @brief Parametrized constructor (loads a Sphere from an input file)
     * @param[in,out] istr Input stream
     */
    explicit Sphere(std::ifstream &istr);

    /// Destructor
    virtual ~Sphere(void);

    virtual bool is_curved(const Grid &g) const;

    /**
     * @brief Setter for Sphere::r
     * @param[in] rin Signed sphere radius (cm)
     */
    void setr(const double rin);

    /**
     * @brief Getter for Sphere::r
     * @return rin Signed sphere radius (cm)
     */
    double getr(void) const;

    /**
     * @brief Setter for Sphere::v
     * @param[in] vin Signed surface velocity (cm/s)
     */
    void setv(const double vin);

    /**
     * @brief Getter for Sphere::v
     * @return vin Signed surface velocity (cm/s)
     */
    double getv(void) const;

    /**
     * @brief Setter for the sign of Sphere::r (Sphere orientation)
     * @param[in] nin Its sign will become the sign of Sphere::r
     */
    void setn(const int nin);

    /**
     * @brief Getter for the sign of Sphere::r (Sphere orientation)
     * @return +1 (outward surface), -1 (inward surface), 0 (zero radius)
     */
    int getn(void) const;

    /**
     * @brief Getter for the location of the center of *this Sphere
     * @return Location of the center (cm)
     */
    Vector3d center_position(const Grid &g) const;

    /**
     * @brief Getter for the velocity of the center of *this Sphere
     * @return Velocity of the center (cm/s)
     */
    Vector3d center_velocity(const Grid &g) const;

    virtual std::string to_string(void) const;

    virtual void load(std::ifstream &istr);

    virtual Vector3d area2_normal_center(const Grid &g, Vector3d &c) const;

    virtual Vector3d normal(const Grid &g) const;

    virtual double area(const Grid &g) const;

    virtual double distance(const Grid &g, const Vector3d &w) const;

    virtual Vector3d subpoint(const Grid &g, const Vector3d &w) const;

    /**
     * @copydoc Face::contains()
     * @return Always "true" for a Sphere, because it has no boundary.
     */
    virtual bool contains(const Grid &g, const Vector3d &w) const;

    virtual RetIntercept intercept(const Grid &g, const Vector3d &p,
                                   const Vector3d &u, const double eqt,
                                   const FaceID &fid) const;
    
    virtual Vector3d velocity(const Grid &g, const Vector3d &w) const;

};

//-----------------------------------------------------------------------------

#endif // SPHERE_H
