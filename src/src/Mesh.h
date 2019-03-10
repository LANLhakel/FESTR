#ifndef MESH_H
#define MESH_H

/**
 * @file Mesh.h
 * @brief Mesh of Zones
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 18 December 2014\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include "Zone.h"

//-----------------------------------------------------------------------------

/// Mesh of Zone objects
class Mesh
{
private:

    /// Number of Zone objects in *this Mesh
    size_t nzones;

    /// List of Zones
    std::vector<const Zone *> zone; // copy ctor and operator = may be needed

public:

    /// Default constructor
    Mesh(void);

    /**
     * @brief Parametrized constructor: reserves room for nin Zone pointers
     * @param[in] nin Number of Zones in *this Mesh
     */
    explicit Mesh(const size_t nin);

    /**
     * @brief Parametrized constructor: loads Mesh from files
     * @param[in] path Directory path to hydro data
     * @param[in] tlabel Time-step index label in string form
     */
    Mesh(const std::string &path, const std::string &tlabel);

    /// Destructor
    ~Mesh(void);

    /// Removes all Zones from *this Mesh
    void clear(void);

    /**
     * @brief Adds a Zone to *this Mesh
     * @param[in] z Pointer to the Zone to be added to *this Mesh
     */
    void add_zone(const Zone * const z);

    /**
     * @brief Getter for the Zone at index i (Mesh::zone)
     * @param[in] i Zone index
     * @return Pointer to the Zone at index i
     */
    const Zone * get_zone(const size_t i) const;

    /**
     * @brief Getter for the size of *this Mesh (Mesh::nzones)
     * @return Number of Zones in *this Mesh
     */
    size_t size(void) const;

    /**
     * @brief Finds which of neighboring Faces contains hit point h
     * @param[in] g Grid
     * @param[in] h Hit point at which Ray exits current Zone
     * @return IDs of the next Zone and Face encountered by the current Ray
     */
    FaceID next_face(const Grid &g, const RetIntercept &h) const;

    /**
     * @brief Constructor helper: loads Mesh from files
     * @param[in] path Directory path to hydro data
     * @param[in] tlabel Time-step index label in string form
     */
    void load(const std::string &path, const std::string &tlabel);

    /**
     * @brief String representation of a Mesh object
     * @return String representation of *this
     */
    std::string to_string(void) const;

};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of Mesh to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o Mesh object
 * @return Reference to output stream
 */

std::ostream & operator << (std::ostream &ost, const Mesh &o);

//-----------------------------------------------------------------------------

#endif // MESH_H
