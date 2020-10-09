#ifndef LANL_ASC_PEM_POLYGON_H_
#define LANL_ASC_PEM_POLYGON_H_

/**
 * @file Polygon.h
 * @brief Convex Polygons (derived from class Face)
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

class Polygon;
typedef std::shared_ptr<Polygon> PolygonPtr;

//-----------------------------------------------------------------------------

/**
 * @brief Convex Polygons (derived from class Face)
 *
 * The number of Node objects defining a Polygon is arbitrary. The Node
 * locations are given via Vector3d objects, which are assumed to be coplanar.
 * \n Some methods in class Polygon (Polygon::area2_normal_center,
 * Polygon::contains) are limited in their applicability to convex Polygons;
 * their generalization to non-convex Polygons is currently left as a future
 * enhancement.
 */
class Polygon : public Face
{
public:

    /// Default constructor
    Polygon();

    /**
     * @brief Parametrized constructor (leaves Face::node, Face::nbr empty)
     * @param[in] my_zone_in Initializes FaceID::my_zone
     * @param[in] my_id_in Initializes FaceID::my_id
     */
    Polygon(const size_t my_zone_in, const short int my_id_in);

    /**
     * @brief Parametrized constructor (loads a Polygon from an input file)
     * @param[in,out] istr Input stream
     */
    explicit Polygon(std::ifstream &istr);

    /// Destructor
    ~Polygon() override;

    bool is_curved(const Grid &g) const override;

    std::string to_string() const override;

    void load(std::ifstream &istr) override;

    /**
     * @copydoc Face::area2_normal_center()
     * @todo Generalize this method to handle non-convex Polygon objects
     */
    Vector3d area2_normal_center(const Grid &g, Vector3d &c) const override;

    Vector3d normal(const Grid &g) const override;

    double area(const Grid &g) const override;

    double distance(const Grid &g, const Vector3d &w) const override;

    Vector3d subpoint(const Grid &g, const Vector3d &w) const override;

    Vector3d face_point(const Grid &g, const Vector3d &w) const override;

    /**
     * @copydoc Face::contains()
     * @todo Generalize this method to handle non-convex Polygon objects
     */
    bool contains(const Grid &g, const Vector3d &w) const override;

    RetIntercept intercept(const Grid &g, const Vector3d &p,
                           const Vector3d &u, const double eqt,
                           const FaceID &fid) const override;

    Vector3d velocity(const Grid &g, const Vector3d &w) const override;
};

//-----------------------------------------------------------------------------

#endif  // LANL_ASC_PEM_POLYGON_H_
