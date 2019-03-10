#ifndef SURFACE_H
#define SURFACE_H

/**
 * @file Surface.h
 * @brief A composite Face that is a collection of other Face objects
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 16 December 2014\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include "Face.h"

//-----------------------------------------------------------------------------

/**
 * @brief A composite Face that is a collection of other Face objects
 *
 * Face::my_zone in constituent Faces serves as that Face's label within *this
 * Surface and the corresponding Face::my_id is set to -1.
 */

class Surface : public Face
{
private:

    /// Number of constituent Face objects in *this Surface
    size_t nfaces;

    /// List of constituent Face objects in *this Surface
    std::vector<const Face *> face; // copy ctor and operator = may be needed

public:

    /// Default constructor
    Surface(void);

    /**
     * @brief Parametrized constructor (leaves Face::node, Face::nbr empty)
     * @param[in] my_zone_in Initializes FaceID::my_zone
     * @param[in] my_id_in Initializes FaceID::my_id
     */
    Surface(const size_t my_zone_in, const short int my_id_in);

    /**
     * @brief Parametrized constructor (leaves Face::node, Face::nbr empty;
     *        reserves space for Surface::face)
     * @param[in] my_zone_in Initializes FaceID::my_zone
     * @param[in] my_id_in Initializes FaceID::my_id
     * @param[in] nin Expected number of constituent Face objects
     */
    Surface(const size_t my_zone_in, const short int my_id_in,
            const size_t nin);

    /**
     * @brief Parametrized constructor (leaves Face::node, Face::nbr empty;
     *        reserves space for Surface::face)
     * @param[in] nin Expected number of constituent Face objects
     */
    explicit Surface(const size_t nin);

    /**
     * @brief Parametrized constructor (loads a Cone from an input file)
     * @param[in,out] istr Input stream
     */
    explicit Surface(std::ifstream &istr);

    /// Destructor
    virtual ~Surface(void);

    virtual void clear(void);

    /**
     * @brief Adds a Face to the end of Surface::face and
     *        increments Surface::nfaces
     * @param[in] f Pointer to Face
     */
    void add_face(const Face * const f);

    /**
     * @brief Retrieves a Face pointer from given location in Surface::face
     * @param[in] i Index of Face within *this Surface
     * @return Pointer to Face
     */
    const Face * get_face(const size_t i) const;

    virtual size_t size(void) const;

    /**
     * @copydoc Face::is_curved()
     * @return Always "true" for a Surface (ignores some special cases)
     */
    virtual bool is_curved(const Grid &g) const;

    virtual std::string to_string(void) const;

    virtual void load(std::ifstream & geometry);

    /**
     * @copydoc Face::area2_normal_center()
     * @return Null vector for a Surface (undefined return);
     *         argument c is left unchanged
     */
    virtual Vector3d area2_normal_center(const Grid &g, Vector3d &c) const;

    /**
     * @copydoc Face::normal()
     * @return Null vector for a Surface (undefined return)
     */
    virtual Vector3d normal(const Grid &g) const;

    virtual double area(const Grid &g) const;

    /**
     * @copydoc Face::distance()
     * @return 0.0 (undefined return)
     */
    virtual double distance(const Grid &g, const Vector3d &w) const;

    /**
     * @copydoc Face::subpoint()
     * @return Null vector for a Surface (undefined return)
     */
    virtual Vector3d subpoint(const Grid &g, const Vector3d &w) const;

    /**
     * @copydoc Face::contains()
     * @return "true", since w was calculated as a constituent Face's intercept
     */
    virtual bool contains(const Grid &g, const Vector3d &w) const;

    virtual RetIntercept intercept(const Grid &g, const Vector3d &p,
                                   const Vector3d &u, const double eqt,
                                   const FaceID &fid) const;

    /**
     * @copydoc Face::velocity()
     * @return Null vector for a Surface (undefined return)
     */
    virtual Vector3d velocity(const Grid &g, const Vector3d &w) const;

};

//-----------------------------------------------------------------------------

#endif // SURFACE_H
