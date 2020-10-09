#ifndef LANL_ASC_PEM_SURFACE_H_
#define LANL_ASC_PEM_SURFACE_H_

/**
 * @file Surface.h
 * @brief A composite Face that is a collection of other Face objects
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 16 December 2014\n
 * Last modified on 24 February 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <Face.h>

//-----------------------------------------------------------------------------

class Surface;
typedef std::shared_ptr<Surface> SurfacePtr;

//-----------------------------------------------------------------------------

/**
 * @brief A composite Face that is a collection of other Face objects
 *
 * Face::my_zone in constituent Faces serves as that Face's label within *this
 * Surface and the corresponding Face::my_id is set to -1.
 */

class Surface : public Face
{
public:

    /// Default constructor
    Surface();

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
    ~Surface() override = default;

    void clear() override;

    /**
     * @brief Adds a Face to the end of Surface::face and
     *        increments Surface::nfaces
     * @param[in] f Pointer to Face
     */
    void add_face(FacePtr f);

    /**
     * @brief Retrieves a Face pointer from given location in Surface::face
     * @param[in] i Index of Face within *this Surface
     * @return Pointer to Face
     */
    FacePtr get_face(const size_t i) const;

    size_t size() const override;

    /**
     * @copydoc Face::is_curved()
     * @return Always "true" for a Surface (ignores some special cases)
     */
    bool is_curved(const Grid &g) const override;

    std::string to_string() const override;

    void load(std::ifstream & geometry) override;

    /**
     * @copydoc Face::area2_normal_center()
     * @return Null vector for a Surface (undefined return);
     *         argument c is left unchanged
     */
    Vector3d area2_normal_center(const Grid &g, Vector3d &c) const override;

    /**
     * @copydoc Face::normal()
     * @return Null vector for a Surface (undefined return)
     */
    Vector3d normal(const Grid &g) const override;

    double area(const Grid &g) const override;

    /**
     * @copydoc Face::distance()
     * @return 0.0 (undefined return)
     */
    double distance(const Grid &g, const Vector3d &w) const override;

    /**
     * @copydoc Face::subpoint()
     * @return Null vector for a Surface (undefined return)
     */
    Vector3d subpoint(const Grid &g, const Vector3d &w) const override;

    Vector3d face_point(const Grid &g, const Vector3d &w) const override;

    /**
     * @copydoc Face::contains()
     * @return "true", since w was calculated as a constituent Face's intercept
     */
    bool contains(const Grid &g, const Vector3d &w) const override;

    RetIntercept intercept(const Grid &g, const Vector3d &p,
                           const Vector3d &u, const double eqt,
                           const FaceID &fid) const override;

    /**
     * @copydoc Face::velocity()
     * @return Null vector for a Surface (undefined return)
     */
    Vector3d velocity(const Grid &g, const Vector3d &w) const override;


private:

    /// Number of constituent Face objects in *this Surface
    size_t nfaces;

    /// List of constituent Face objects in *this Surface
    std::vector<FacePtr> face;
};

//-----------------------------------------------------------------------------

#endif  // LANL_ASC_PEM_SURFACE_H_
