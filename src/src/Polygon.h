#ifndef POLYGON_H
#define POLYGON_H

/**
 * @file Polygon.h
 * @brief Convex Polygons (derived from class Face)
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
    Polygon(void);

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
    virtual ~Polygon(void);

    virtual bool is_curved(const Grid &g) const;

    virtual std::string to_string(void) const;

    virtual void load(std::ifstream &istr);

    /**
     * @copydoc Face::area2_normal_center()
     * @todo Generalize this method to handle non-convex Polygon objects
     */
    virtual Vector3d area2_normal_center(const Grid &g, Vector3d &c) const;

    virtual Vector3d normal(const Grid &g) const;

    virtual double area(const Grid &g) const;

    virtual double distance(const Grid &g, const Vector3d &w) const;

    virtual Vector3d subpoint(const Grid &g, const Vector3d &w) const;

    /**
     * @copydoc Face::contains()
     * @todo Generalize this method to handle non-convex Polygon objects
     */
    virtual bool contains(const Grid &g, const Vector3d &w) const;

    virtual RetIntercept intercept(const Grid &g, const Vector3d &p,
                                   const Vector3d &u, const double eqt,
                                   const FaceID &fid) const;

    virtual Vector3d velocity(const Grid &g, const Vector3d &w) const;

};

//-----------------------------------------------------------------------------

#endif // POLYGON_H
