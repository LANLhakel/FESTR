#ifndef CONE_H
#define CONE_H

/**
 * @file Cone.h
 * @brief Conical ribbons for 2-D RZ geometry (derived from class Face)
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 14 May 2015\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include "Face.h"

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
private:

    /// Cone with |dz| <= SMALL is a flat hoop
    static const double SMALL;

public:

    /// Default constructor
    Cone(void);

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
    virtual ~Cone(void);

    virtual bool is_curved(const Grid &g) const;

    virtual std::string to_string(void) const;

    virtual void load(std::ifstream &istr);

    virtual Vector3d area2_normal_center(const Grid &g, Vector3d &c) const;

    virtual Vector3d normal(const Grid &g) const;

    virtual double area(const Grid &g) const;

    virtual double distance(const Grid &g, const Vector3d &w) const;

    virtual Vector3d subpoint(const Grid &g, const Vector3d &w) const;

    virtual bool contains(const Grid &g, const Vector3d &w) const;

    virtual RetIntercept intercept(const Grid &g, const Vector3d &p,
                                   const Vector3d &u, const double eqt,
                                   const FaceID &fid) const;

    virtual Vector3d velocity(const Grid &g, const Vector3d &w) const;

};

//-----------------------------------------------------------------------------

#endif // CONE_H
