#ifndef LANL_ASC_PEM_SPHERE_H_
#define LANL_ASC_PEM_SPHERE_H_

/**
 * @file Sphere.h
 * @brief Spherical shells (derived from class Face)
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 21 November 2014\n
 * Last modified on 24 February 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <Face.h>

//-----------------------------------------------------------------------------

class Sphere;
typedef std::shared_ptr<Sphere> SpherePtr;

//-----------------------------------------------------------------------------

/// Spherical shells (derived from class Face)
class Sphere : public Face
{
public:

    /// Default constructor
    Sphere();

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
    ~Sphere() override;

    bool is_curved(const Grid &g) const override;

    /**
     * @brief Setter for Sphere::r
     * @param[in] rin Signed sphere radius (cm)
     */
    void setr(const double rin);

    /**
     * @brief Getter for Sphere::r
     * @return rin Signed sphere radius (cm)
     */
    double getr() const;

    /**
     * @brief Setter for Sphere::v
     * @param[in] vin Signed surface velocity (cm/s)
     */
    void setv(const double vin);

    /**
     * @brief Getter for Sphere::v
     * @return vin Signed surface velocity (cm/s)
     */
    double getv() const;

    /**
     * @brief Setter for the sign of Sphere::r (Sphere orientation)
     * @param[in] nin Its sign will become the sign of Sphere::r
     */
    void setn(const int nin);

    /**
     * @brief Getter for the sign of Sphere::r (Sphere orientation)
     * @return +1 (outward surface), -1 (inward surface), 0 (zero radius)
     */
    int getn() const;

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

    std::string to_string() const override;

    void load(std::ifstream &istr) override;

    Vector3d area2_normal_center(const Grid &g, Vector3d &c) const override;

    Vector3d normal(const Grid &g) const override;

    double area(const Grid &g) const override;

    double distance(const Grid &g, const Vector3d &w) const override;

    Vector3d subpoint(const Grid &g, const Vector3d &w) const override;

    Vector3d face_point(const Grid &g, const Vector3d &w) const override;

    /**
     * @copydoc Face::contains()
     * @return Always "true" for a Sphere, because it has no boundary.
     */
    bool contains(const Grid &g, const Vector3d &w) const override;

    RetIntercept intercept(const Grid &g, const Vector3d &p,
                                   const Vector3d &u, const double eqt,
                                   const FaceID &fid) const override;
    
    Vector3d velocity(const Grid &g, const Vector3d &w) const override;


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
};

//-----------------------------------------------------------------------------

#endif  // LANL_ASC_PEM_SPHERE_H_
