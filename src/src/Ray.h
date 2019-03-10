#ifndef RAY_H
#define RAY_H

/**
 * @file Ray.h
 * @brief Ray carrying a spectrum and its own current position and direction
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 24 December 2014\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include "Grid.h"
#include "Mesh.h"
#include <string>
#include <iostream>
#include <stack>
#include <utility>

//-----------------------------------------------------------------------------

/// Auxiliary structure for Ray-tracing
struct Waypoint
{
    /// Face hit by Ray on exit from Zone
    FaceID outface;

    /// Face hit by Ray on entry into Zone
    FaceID inface;

    /// Hitpoint (intercept) = location of *this Waypoint
    Vector3d hitpt;

    /// Default constructor
    Waypoint(void);

    /**
     * @brief Parametrized constructor
     * @param[in] hp Initializes location of *this Waypoint (Waypoint::hitpt)
     */
    explicit Waypoint(const Vector3d &hp);

    /**
     * @brief Parametrized constructor
     * @param[in] oface Initializes Waypoint::outface
     * @param[in] iface Initializes Waypoint::inface
     * @param[in] hp Initializes location of *this Waypoint (Waypoint::hitpt)
     */
    Waypoint(const FaceID &oface, const FaceID &iface, const Vector3d &hp);
};

//-----------------------------------------------------------------------------

/// Ray path
typedef std::stack<Waypoint> RayStack;

/// Integer labels for Detector use: first -> theta,x, second -> phi,y
typedef std::pair<size_t, size_t> IntPair;

/// Axis of the Ray bundle / Ray origin
const IntPair INT_PAIR_00 = IntPair(0, 0);

//-----------------------------------------------------------------------------

/// Ray carrying a spectrum and its own current position and direction
class Ray
{
private:

    /// Progress indentation level
    int level;

    /// Frequency of Progress prints
    size_t freq;

    /// Size of the photon-energy grid
    size_t n;

    /// Range of hv-grid (lower limit)
    size_t jmin;

    /// Range of hv-grid (upper limit)
    size_t jmax;

    /// Number of Zones crossed by *this Ray
    size_t nzones;

    /// Number of digits needed to represent Ray::nzones
    int nzd;
    
    /// Zone cursor along the path of *this Ray
    size_t iz;

    /// Current distance (cm) traveled by *this Ray
    double distance;

    /// Tracking of partial results along *this Ray
    bool tracking;

    /// Output filename root for partial spectral results
    std::string froot;

    /// Header for partial spectral results
    std::string hroot;
    
    /**
     * @brief Ray constructor helper
     * @param[in] nin Initializes sizes of Ray::em, Ray::ab, Ray::sc
     * @param[in] rin Initializes Waypoint position (Ray::wpt)
     */
    void init(const size_t nin, const Vector3d &rin);

public:

    /// ID of Detector that *this Ray hits at the end of its path
    int diag_id;

    /// ID of Detector's spatial patch hit by *this Ray
    IntPair patch_id;

    /// ID of direction from which *this Ray hits its Detector patch
    IntPair bundle_id;

    /// Current Ray position
    Vector3d r;

    /// Current Ray velocity
    Vector3d v;

    /// "true" in analysis, "false" in postprocessing mode
    bool analysis;

    /// ID of current Zone
    size_t zid;

    /// Current Ray specific intensity in W / cm2 / sr / eV
    ArrDbl y;

    /// Ray trajectory through Mesh as a sequence of Waypoint objects
    RayStack wpt;

    /// Electron temperature Database access index saved from previous Zone
    size_t ite;

    /// Radiation temperature Database access index saved from previous Zone
    size_t itr;

    /// Electron density Database access index saved from previous Zone
    size_t ine;

    /// Current Zone monochromatic emissivity in W / cm3 / sr / eV
    ArrDbl em;

    /// Current Zone monochromatic absorption opacity in 1 / cm
    ArrDbl ab;

    /// Current Zone monochromatic scattering in 1 / cm
    ArrDbl sc;

//-----------------------------------------------------------------------------

    /// Default constructor
    Ray(void);

    /**
     * @brief Parametrized constructor
     * @param[in] level_in Initializes Ray::level
     * @param[in] freq_in Initializes Ray::freq
     * @param[in] nin Initializes Ray::n
     * @param[in] jmin_in Initializes Ray::jmin
     * @param[in] jmax_in Initializes Ray::jmax
     * @param[in] tracking_in Initializes Ray::tracking
     * @param[in] rin Initializes Ray::r
     * @param[in] vin Initializes Ray::v
     * @param[in] analysis_in Initializes Ray::analysis
     * @param[in] froot_in Initializes Ray::froot
     * @param[in] hroot_in Initializes Ray::hroot
     */
    Ray(const int level_in, const size_t freq_in, const size_t nin,
        const size_t jmin_in, const size_t jmax_in, const bool tracking_in,
        const Vector3d &rin, const Vector3d &vin, const bool analysis_in,
        const std::string &froot_in, const std::string &hroot_in);

    /**
     * @brief Parametrized constructor
     * @param[in] level_in Initializes Ray::level
     * @param[in] freq_in Initializes Ray::freq
     * @param[in] nin Initializes Ray::n
     * @param[in] jmin_in Initializes Ray::jmin
     * @param[in] jmax_in Initializes Ray::jmax
     * @param[in] tracking_in Initializes Ray::tracking
     * @param[in] rin Initializes Ray::r
     * @param[in] vin Initializes Ray::v
     * @param[in] analysis_in Initializes Ray::analysis
     * @param[in] yin Initializes Ray::y
     * @param[in] froot_in Initializes Ray::froot
     * @param[in] hroot_in Initializes Ray::hroot
     */
    Ray(const int level_in, const size_t freq_in, const size_t nin,
        const size_t jmin_in, const size_t jmax_in, const bool tracking_in,
        const Vector3d &rin, const Vector3d &vin, const bool analysis_in,
        const ArrDbl &yin,
        const std::string &froot_in, const std::string &hroot_in);

    /// Destructor
    ~Ray(void);

    /**
     * @brief Getter for size of the spectrum (Ray::n)
     * @return Number of photon-energy points in the spectrum
     */
    size_t size(void) const;

    /**
     * @brief Getter for size of the Ray's trajectory (Ray::nzones)
     * @return Number of Zones crossed by *this Ray
     */
    size_t get_nzones(void) const;

    /**
     * @brief Getter for Ray::tracking
     * @return Flag for printing of partial results along *this Ray
     */
    bool get_tracking(void) const;

    /**
     * @brief Absolute difference between two Rays
     * @param[in] o Ray
     * @return See Definition
     */
    double abs_diff(const Ray &o) const;

    /**
     * @brief Sets either a flat or a Planckian backlighter into Ray::y
     * @param[in] back_type "flat" (constant), or "blackbody"
     * @param[in] back_value Backlighter value or Planckian temperature (eV)
     * @param[in] hv Photon-energy grid under Ray::y
     */
    void set_backlighter(const std::string &back_type,
                         const double back_value, std::vector<double> &hv);

    /**
     * @brief Ray tracing -> builds Ray::wpt stack of Waypoint objects
     * @param[in] g Grid of Node objects
     * @param[in] m Mesh of Zone objects
     */
    void trace(const Grid &g, const Mesh &m);

    /**
     * @brief Apply 1D analytic transport solution to update Ray::y
     * @param[in] ct Ray chord length across current Zone
     */
    void transport(const double ct);

    /**
     * @brief Transport *this Ray across current Zone, also write the current
     *        spectrum on exit from this Zone, if Ray::tracking is true
     * @param[in] z Current Zone
     * @param[in] d Database
     * @param[in] tbl Table of materials
     * @param[in] symmetry "spherical" or "none"
     * @param[in] ix Ray patch ID (used if symmetry == "spherical" to save
     *            or retrieve optical data for the current Zone)
     * @param[in] ndmesh Number of digits needed to represent the total
                  number of Zones in the Mesh
     */
    void cross_Zone(const Zone *z, const Database &d, const Table &tbl,
                    const std::string &symmetry, const size_t ix,
                    const int ndmesh);

    /**
     * @brief Transport *this Ray across Mesh
     * @param[in] m Mesh
     * @param[in] d Database
     * @param[in] tbl Table of materials
     * @param[in] symmetry "spherical" or "none"
     * @param[in] ix Ray patch ID (used if symmetry == "spherical" to save
     *            or retrieve optical data from Zones to speed up calculation)
     */
    void cross_Mesh(const Mesh &m, const Database &d, const Table &tbl,
                    const std::string &symmetry, const size_t ix);

    /**
     * @brief String representation of a Ray object
     * @return String representation of *this
     */
    std::string to_string(void) const;

};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of Ray to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o Ray object
 * @return Reference to output stream
 */

std::ostream & operator << (std::ostream &ost, const Ray &o);

//-----------------------------------------------------------------------------

#endif // RAY_H
