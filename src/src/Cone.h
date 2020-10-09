#ifndef LANL_ASC_PEM_CELL_CONE_H_
#define LANL_ASC_PEM_CELL_CONE_H_

/**
 * @file Cone.h
 * @brief Conical ribbons for 2-D RZ geometry (derived from class Face)
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 14 May 2015\n
 * Last modified on 8 October 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <Face.h>

//-----------------------------------------------------------------------------

class Cone;
typedef std::shared_ptr<Cone> ConePtr;

//-----------------------------------------------------------------------------

/**
 * @brief Conical ribbons for 2-D RZ geometry (derived from class Face)
 *
 * Each Cone consists of two Node objects, whose order defines the orientation
 * of the Cone. In the Vector3d components of each Node the x coordinate
 * represents R, and the y coordinate represents Z. The z coordinates of Nodes'
 * Vector3d's are set to zero, and are ignored in class Cone.
 */
class Cone : public Face
{
public:

    /// Default constructor
    Cone();

    /**
     * @brief Parametrized constructor (leaves Face::node, Face::nbr empty)
     * @param[in] my_zone_in Initializes FaceID::my_zone
     * @param[in] my_id_in Initializes FaceID::my_id
     */
    Cone(const size_t my_zone_in, const short int my_id_in);

    /**
     * @brief Parametrized constructor (loads a Cone from an input file)
     * @param[in,out] istr Input stream
     */
    explicit Cone(std::ifstream &istr);

    /// Destructor
    ~Cone() override;

    bool is_curved(const Grid &g) const override;

    std::string to_string() const override;

    void load(std::ifstream &istr) override;

    Vector3d area2_normal_center(const Grid &g, Vector3d &c) const override;

    Vector3d normal(const Grid &g) const override;

    double area(const Grid &g) const override;

    double distance(const Grid &g, const Vector3d &w) const override;

    Vector3d subpoint(const Grid &g, const Vector3d &w) const override;

    Vector3d face_point(const Grid &g, const Vector3d &w) const override;

    bool contains(const Grid &g, const Vector3d &w) const override;

    RetIntercept intercept(const Grid &g, const Vector3d &p,
                           const Vector3d &u, const double eqt,
                           const FaceID &fid) const override;

    Vector3d velocity(const Grid &g, const Vector3d &w) const override;

    /**
     * @brief End points of *this Cone for a given azimuthal angle
     * @param[in] g Grid
     * @param[in] phi Azimuthal angle (radians)
     * @return Pair of Vector3d objects with the "upper" one as first
     */
    std::pair<Vector3d, Vector3d> get_endpoints(const Grid &g,
                                                const double phi) const;


private:

    /// Cone with |dz| <= SMALL is a flat hoop
    static const double SMALL; // centimeters

    /// Hit points cannot be closer to a Node than this value
    static const double MINIMUM_DISTANCE; // centimeters

    /// Effective zero squared distance near one of the edges
    static const double ZERO; // centimeters squared
};

//-----------------------------------------------------------------------------

#endif // LANL_ASC_PEM_CELL_CONE_H_
