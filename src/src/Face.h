#ifndef LANL_ASC_PEM_FACE_H_
#define LANL_ASC_PEM_FACE_H_

/**
 * @file Face.h
 * @brief Abstract base class for various Face types that define Zone objects
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 20 November 2014\n
 * Last modified on 26 February 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <constants.h>
#include <Grid.h>
#include <Node.h>
#include <utils.h>
#include <Vector3d.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------

class Face;
typedef std::shared_ptr<Face> FacePtr;

//-----------------------------------------------------------------------------

/// Pair of integer labels identifying a Face within its Zone
struct FaceID
{
    /// ID of the Zone to which the Face belongs
    size_t my_zone;

    /// Face ID local to its Zone
    short int my_id;

    /// Default constructor
    FaceID(): my_zone(0), my_id(-2) {}

    /**
     * @brief Parametrized constructor
     * @param[in] zid_in Initializes FaceID::my_zone
     * @param[in] fid_in Initializes FaceID::my_id
     */
    FaceID(const size_t zid_in, const short int fid_in):
        my_zone(zid_in), my_id(fid_in) {}

    /// Overloaded "equal" comparison operator for class FaceID
    bool operator == (const FaceID &o) const
    {
        return my_zone == o.my_zone  &&  my_id == o.my_id;
    }

    /// Overloaded "not equal" comparison operator for class FaceID
    bool operator != (const FaceID &o) const
    {
        return !(*this == o);
    }

    /**
     * @brief String representation of a FaceID object
     * @return String representation of *this
     */
    std::string to_string() const
    {
        std::string s(utils::int_to_string(my_zone, ' ', cnst::INT_WIDTH));
        s += utils::int_to_string(my_id, ' ', cnst::INT_WIDTH);
        return s;
    }

};

/**
 * @brief Send string version of FaceID to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o FaceID object
 * @return Reference to output stream
 */
std::ostream & operator << (std::ostream &ost, const FaceID &o);

//-----------------------------------------------------------------------------

/// Encapsulates and returns info about Ray intersections with Face objects
struct RetIntercept
{
    /// Time of flight (seconds) to *this intercept
    double t;

    /// Location of *this intercept
    Vector3d w;

    /// FaceID of the Face where *this intercept is located
    FaceID fid;

    /// Flags success or failure to locate *this next intercept
    bool is_found;

    /// Default constructor
    RetIntercept(): t(Vector3d::get_big()), w(), fid(), is_found(false) {}
};

//-----------------------------------------------------------------------------

/// Abstract base class for various Face types that define Zone objects
class Face
{
public:

    /// Fixed label of the bounding Sphere
    static const FaceID BOUNDING_SPHERE;

    /// Default constructor
    Face();

    /**
     * @brief Parametrized constructor (leaves Face::node, Face::nbr empty)
     * @param[in] my_zone_in Initializes FaceID::my_zone
     * @param[in] my_id_in Initializes FaceID::my_id
     */
    Face(const size_t my_zone_in, const short int my_id_in);

    /// Destructor
    virtual ~Face();

    /// Reset *this Face to the state initialized by Face::Face
    virtual void clear();

    /**
     * @brief Setter for Face::my_zone
     * @param[in] my_zone_in ID of the Zone to which *this Face belongs
     */
    void set_my_zone(const size_t my_zone_in);

    /**
     * @brief Getter for Face::my_zone
     * @return ID of the Zone to which *this Face belongs
     */
    size_t get_my_zone() const;

    /**
     * @brief Setter for Face::my_id
     * @param[in] my_id_in Face ID local to its Zone
     */
    void set_my_id(const short int my_id_in);
    
    /**
     * @brief Getter for Face::my_id
     * @return Face ID local to its Zone
     */
    short int get_my_id() const;

    /**
     * @brief Getter for the size of Face::node
     * @return Number of Node objects forming *this Face
     */
    virtual size_t size() const;

    /**
     * @brief Flag for the shape of *this Face
     * @return "false" for Polygon and disk-like Cone, "true" otherwise
     */
    virtual bool is_curved(const Grid &g) const = 0;

    /**
     * @brief Flag for the shape of *this Face
     * @return The logical complement of Face::is_curved
     */
    bool is_flat(const Grid &g) const;

    /**
     * @brief Adds a Node ID to the end of Face::node
     * @param[in] i Node ID
     */
    void add_node(const size_t i);

    /**
     * @brief Retrieves the Node ID from given location in Face::node
     * @param[in] i Index of Node within *this Face
     * @return Node ID; throws an exception if i is out of range
     */
    size_t get_node(const size_t i) const;

    /**
     * @brief Absolute difference between two Face objects
     * @param[in] o Face
     * @return See Definition
     */
    double abs_diff(const Face &o) const;

    /**
     * @brief String representation of a Face object
     * @return String representation of *this
     */
    virtual std::string to_string() const;

    /**
     * @brief Loads a Face from an input file
     * @param[in,out] istr Input stream
     * @param[in] nnodes Number of Node objects defining *this Face
     */
    void load_face(std::ifstream &istr, const size_t nnodes);

    /**
     * @brief Constructor helper: loads a Face from an input file
     * @param[in,out] istr Input stream
     */
    virtual void load(std::ifstream &istr) = 0;

    /**
     * @brief Adds a neighbor's FaceID to the end of Face::nbr
     * @param[in] zone_in Zone ID
     * @param[in] face_in Face ID
     */
    void add_neighbor(const size_t zone_in, const short int face_in);

    /**
     * @brief Getter for the size of Face::nbr
     * @return Number of neighbors that *this Face has
     */
    size_t num_nbr() const;

    /**
     * @brief Retrieves neighbor's FaceID from given location in Face::nbr
     * @param[in] i Index of neighbor within *this Face
     * @return Neighbor FaceID; throws an exception if i is out of range
     */
    FaceID get_neighbor(const size_t i) const;

    /**
     * @brief Normal vector of *this oriented Face of length 2*area;
     *        center of *this Face is also calculated as a byproduct
     * @param[in] g Grid of Node objects
     * @param[out] c Center of *this Face
     * @return Normal vector of *this Face
     */
    virtual Vector3d area2_normal_center(const Grid &g, Vector3d &c)
                                         const = 0;

    /**
     * @brief Unit normal vector of *this oriented Face
     * @param[in] g Grid of Node objects
     * @return Unit normal vector of *this Face
     */
    virtual Vector3d normal(const Grid &g) const = 0;

    /**
     * @brief Area of *this Face
     * @param[in] g Grid of Node objects
     * @return Area of *this Face
     */
    virtual double area(const Grid &g) const = 0;

    /**
     * @brief Signed distance of a point from *this Face
     * @param[in] g Grid of Node objects
     * @param[in] w Location of a point
     * @return Signed distance between w and *this
     */
    virtual double distance(const Grid &g, const Vector3d &w) const = 0;

    /**
     * @brief Location of a point's subpoint on *this Face
     * @param[in] g Grid of Node objects
     * @param[in] w Location of a point
     * @return Intersection of *this Face with the perpendicular dropped from w
     */
    virtual Vector3d subpoint(const Grid &g, const Vector3d &w) const = 0;

    /**
     * @brief A reference point on *this Face (used by Zone::zone_point)
     * @param[in] g Grid of Node objects
     * @param[in] w Location of a point
     * @return A reference point on *this Face
     */
    virtual Vector3d face_point(const Grid &g, const Vector3d &w) const = 0;

    /**
     * @brief Flags whether a point is above *this oriented Face
     * @param[in] g Grid of Node objects
     * @param[in] w Point's location
     * @return "true" or "false"
     */
    bool has_above(const Grid &g, const Vector3d &w) const;

    /**
     * @brief Flags whether a point is below *this oriented Face
     * @param[in] g Grid of Node objects
     * @param[in] w Point's location
     * @return "true" or "false"
     */
    bool has_below(const Grid &g, const Vector3d &w) const;

    /**
     * @brief Flags whether a point is within *this Face
     * @param[in] g Grid of Node objects
     * @param[in] w Point's location
     * @return "true" or "false"
     */
    virtual bool contains(const Grid &g, const Vector3d &w) const = 0;

    /**
     * @brief Ray intercept with *this Face
     * @param[in] g Grid of Node objects
     * @param[in] p Ray starting point
     * @param[in] u Ray velocity
     * @param[in] eqt Tolerance parameter for comparisons with zero
     * @param[in] fid FaceID of the Face where p is located
     * @return RetIntercept struct with next intercept's info
     */
    virtual RetIntercept intercept(const Grid &g, const Vector3d &p,
                                   const Vector3d &u,
                                   const double eqt, const FaceID &fid)
                                   const = 0;

    /**
     * @brief Velocity of a point on *this Face
     * @param[in] g Grid of Node objects
     * @param[in] w Location on *this Face
     * @return Velocity at w interpolated from *this Face's Node velocities
     */
    virtual Vector3d velocity(const Grid &g, const Vector3d &w) const = 0;


private:

    /// ID of the Zone to which *this Face belongs
    size_t my_zone;

    /// Face ID local to its Zone
    short int my_id;

    /// ID's of ordered Node objects defining *this Face
    std::vector<size_t> node;

    /// Neighbors: Faces from other Zone objects in contact with *this Face
    std::vector<FaceID> nbr;
};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of Face to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o Face object
 * @return Reference to output stream
 */
std::ostream & operator << (std::ostream &ost, const Face &o);

//-----------------------------------------------------------------------------

#endif  // LANL_ASC_PEM_FACE_H_
