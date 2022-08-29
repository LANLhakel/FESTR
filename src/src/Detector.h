#ifndef LANL_ASC_PEM_DETECTOR_H_
#define LANL_ASC_PEM_DETECTOR_H_

/**
 * @file Detector.h
 * @brief Detector objects
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 28 January 2015\n
 * Last modified on 27 July 2022
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

/*=============================================================================

pmh_2015_0210

=============================================================================*/

#include <ArrDbl.h>
#include <Database.h>
#include <Goal.h>
#include <Grid.h>
#include <Hydro.h>
#include <Mesh.h>
#include <Polygon.h>
#include <Progress.h>
#include <Ray.h>
#include <Vector3d.h>

#include <map>
#include <string>

//-----------------------------------------------------------------------------

/// contains ArrDbl objects indexed by a pair of integers
typedef std::map<IntPair, ArrDbl> SpecPatch;

//-----------------------------------------------------------------------------

/// Detector object
class Detector
{
public:

    /// Space-resolved, time-integrated spectra
    SpecPatch yt;

    /// Space-integrated, time-integrated spectrum
    ArrDbl yst;

//-----------------------------------------------------------------------------

    /// Default constructor
    Detector();

    /**
     * @brief Parametrized constructor
     * @param[in] freq_patch_in Initializes Detector::freq_patch
     * @param[in] freq_Ray_in Initializes Detector::freq_Ray
     * @param[in] freq_trace_in Initializes Detector::freq_trace
     * @param[in] diag_path Path to the Diagnostics definitions directory
     * @param[in] dname_in Initializes Detector::dname
     * @param[in] path_in Initializes Detector::path
     * @param[in] dbase_path Database path
     * @param[in] sym_in Initializes Detector::symmetry
     * @param[in] my_id_in Initializes Detector::my_id
     * @param[in] rc_in Initializes Detector::rc
     * @param[in] rx_in Initializes Detector::rx
     * @param[in] ry_in Initializes Detector::ry
     * @param[in] dx_in Initializes Detector::dx
     * @param[in] dy_in Initializes Detector::dy
     * @param[in] nhv_in Initializes Detector::jmin
     * @param[in] hv_min Initializes Detector::hvmin
     * @param[in] hv_max Initializes Detector::hvmax
     * @param[in] fwhm_in Initializes Detector::fwhm
     * @param[in] pc_in Pointing location
     * @param[in] back_type_in Initializes Detector::back_type
     * @param[in] back_value_in
     *            backlighter's value (W/cm2/sr/eV) if back_type == "flat";
     *            backlighter's temperature (eV) if back_type == "blackbody";
     *            backlighter's file name if back_type == "file"
     * @param[in] tracking_in Initializes Detector::tracking
     * @param[in] write_Ray_in Initializes Detector::write_Ray_in
     */
    Detector(const size_t freq_patch_in, const size_t freq_Ray_in,
             const size_t freq_trace_in, const std::string &diag_path,
             const std::string &dname_in, const std::string &path_in,
             const std::string &dbase_path, const std::string &sym_in,
             const int my_id_in, const Vector3d &rc_in,
             const Vector3d &rx_in, const Vector3d &ry_in,
             const double dx_in, const double dy_in,
             const size_t nhv_in, const double hv_min, const double hv_max,
             const double fwhm_in, const Vector3d &pc_in,
             const std::string &back_type_in,
             const std::string &back_value_in, const bool tracking_in,
             const bool write_Ray_in);

    /**
     * @brief Absolute difference between two Detectors
     * @param[in] o Detector
     * @return See Definition
     */
    double abs_diff(const Detector &o) const;

    /**
     * @brief String representation of a Detector object
     * @return String representation of *this
     */
    std::string to_string() const;

    /**
     * @brief Setter for Ray bundle variables
     * @param[in] theta_max_in Initializes Detector::theta_max
     * @param[in] ntheta_in Initializes Detector::ntheta,
     *            Detector::nthetad, Detector::dtheta, Detector::dtheta2
     * @param[in] nphi_in Initializes Detector::nphi
     */
    void set_bundle(const double theta_max_in,
                    const size_t ntheta_in, const size_t nphi_in);

    /**
     * @brief Getter for Detector::dname
     * @return *this Detector's name
     */
    std::string get_dname() const;

    /**
     * @brief Getter for Detector::path
     * @return Path to output files for *this Detector
     */
    std::string get_path() const;

    /**
     * @brief Getter for Detector::symmetry
     * @return "none", "spherical", ("cylindrical" to be added)
     */
    std::string get_symmetry() const;

    /**
     * @brief Getter for Detector::my_id
     * @return *this Detector's label within Diagnostics
     */
    int get_my_id() const;

    /**
     * @brief Getter for Detector::rc
     * @return Central point
     */
    Vector3d get_rc() const;

    /**
     * @brief Getter for Detector::ro
     * @return Lower-leftmost Ray contact point
     */
    Vector3d get_ro() const;

    /**
     * @brief Getter for Detector::rx
     * @return Axes half-vector
     */
    Vector3d get_rx() const;

    /**
     * @brief Getter for Detector::ry
     * @return Axes half-vector
     */
    Vector3d get_ry() const;

    /**
     * @brief Getter for Detector::ex
     * @return Unit vector for *this plane
     */
    Vector3d get_ex() const;

    /**
     * @brief Getter for Detector::ey
     * @return Unit vector for *this plane
     */
    Vector3d get_ey() const;

    /**
     * @brief Getter for Detector::ez
     * @return Unit vector for *this plane
     */
    Vector3d get_ez() const;

    /**
     * @brief Getter for Detector::pc
     * @return Pointing location
     */
    Vector3d get_pc() const;

    /**
     * @brief Getter for Detector::bx
     * @return Unit vector for Ray bundles
     */
    Vector3d get_bx() const;

    /**
     * @brief Getter for Detector::by
     * @return Unit vector for Ray bundles
     */
    Vector3d get_by() const;

    /**
     * @brief Getter for Detector::bz
     * @return Unit vector for Ray bundles
     */
    Vector3d get_bz() const;

    /**
     * @brief Getter for Detector::nhv
     * @return Actual size of ArrDbl spectrum
     */
    size_t get_nhv() const;

    /**
     * @brief Getter for Detector::hv
     * @return Actual photon energy grid (eV)
     */
    std::vector<double> get_hv() const;

    /**
     * @brief Getter for Detector::jmin
     * @return Index for hvmin within hv_grid.txt
     */
    size_t get_jmin() const;

    /**
     * @brief Getter for Detector::hvmin
     * @return Actual photon energy range: lower limit (eV)
     */
    double get_hvmin() const;

    /**
     * @brief Getter for Detector::jmax
     * @return Index for hvmax within hv_grid.txt
     */
    size_t get_jmax() const;

    /**
     * @brief Getter for Detector::hvmax
     * @return Actual photon energy range: upper limit (eV)
     */
    double get_hvmax() const;

    /**
     * @brief Getter for Detector::fwhm
     * @return Broadening half-width from instrumental resolution
     */
    double get_fwhm() const;

    /**
     * @brief Getter for Detector::back_type
     * @return Backlighter value type: "flat" or "blackbody"
     */
    std::string get_back_type() const;

    /**
     * @brief Getter for Detector::back_value for the backlighter
     * @return "flat" (W/cm2/sr/eV); or temperature (eV)
     */
    double get_back_value() const;

    /**
     * @brief Getter for Detector::yback
     * @return Backlighter values
     */
    std::vector<double> get_backlighter() const;

    /**
     * @brief Getter for Detector::tracking
     * @return Flag for printing of partial results along Rays
     */
    bool get_tracking() const;

    /**
     * @brief Getter for Detector::nx
     * @return Number of intervals along x dimension
     */
    size_t get_nx() const;

    /**
     * @brief Getter for Detector::ny
     * @return Number of intervals along y dimension
     */
    size_t get_ny() const;

    /**
     * @brief Getter for coordinates of the i-th Node
     * @param[in] i Index of vertex
     * @return The r component of Vector3d
     */
    Vector3d get_vertex(const size_t i) const;

    /**
     * @brief Getter for Detector::ux
     * @return Neighboring Ray spacing vector
     */
    Vector3d get_ux() const;

    /**
     * @brief Getter for Detector::uy
     * @return Neighboring Ray spacing vector
     */
    Vector3d get_uy() const;

    /**
     * @brief Getter for maximum polar angle for Ray bundle
     * @param[in] sc Center of bounding Sphere
     * @param[in] sr Distance from bounding Sphere center to touch point
     * @return Angle in radians
     */
    double compute_theta_max(const Vector3d &sc, const double sr);

    /**
     * @brief Getter for Detector::theta_max
     * @return Ray bundle's half angle (radians)
     */
    double get_theta_max() const;

    /**
     * @brief Getter for Detector::ntheta
     * @return Number of intervals in polar direction
     */
    size_t get_ntheta() const;

    /**
     * @brief Getter for Detector::nphi
     * @return Minimum number of intervals in azimuthal direction
     */
    size_t get_nphi() const;

    /**
     * @brief Azimuthal discretization of a given polar direction
     * @param[in] i Polar-angle index
     * @return Number of intervals in azimuthal direction
     */
    size_t calculate_nphi(const size_t i) const;

    /**
     * @brief Calculate polar and azimuthal angles
     * @param[in] direction Integer indeces of the two angles
     * @return Pair of angles (first=polar, second=azimuthal)
     */
    std::pair<double, double> theta_phi(const IntPair &direction) const;

    /**
     * @brief Getter for Detector::dtheta
     * @return Spacing (radians) in polar direction
     */
    double get_dtheta() const;

    /**
     * @brief Getter for Detector::dtheta2
     * @return Half spacing (radians) in polar direction
     */
    double get_dtheta2() const;

    /**
     * @brief Converter of Ray direction vector
     * @param[in] v Direction vector local to *this Detector
     * @return Direction vector in the global coordinate system
     */
    Vector3d local_to_global(const Vector3d &v) const;

    /**
     * @brief Create and transport an individual Ray
     * @param[in] parent Pointer to the previous level's Progress object
     * @param[in] patch ID of the given spatial patch of *this Detector
     * @param[in] direction Direction ID of the Ray
     * @param[in] g Reference to the current Grid object
     * @param[in] m Reference to the current Mesh object
     * @param[in] d Reference to the current Database object
     * @param[in] tbl Reference to the current Table object
     * @param[in] it Current time step index
     * @param[in] froot Root of the filename for the current spatial patch
     * @param[in] hroot Root of the file header for the current spatial patch
     * @param[in] tname Root of the filename for the current time interval
     * @param[in] gol Reference to the current Goal object
     */
    void do_Ray(Progress *parent,
                const IntPair &patch, const IntPair &direction,
                const Grid &g, const Mesh &m, const Database &d,
                const Table &tbl, const size_t it,
                const std::string &froot, const std::string &hroot,
                const std::string &tname, Goal &gol);

    /**
     * @brief Transport all Rays for the given spatial patch of *this Detector
     * @param[in] parent Pointer to the previous level's Progress object
     * @param[in] patch ID of the given spatial patch of *this Detector
     * @param[in] g Reference to the current Grid object
     * @param[in] m Reference to the current Mesh object
     * @param[in] d Reference to the current Database object
     * @param[in] tbl Reference to the current Table object
     * @param[in] it Current time step index
     * @param[in] t Current time instant (seconds)
     * @param[in] dt Current time step size (seconds)
     * @param[in] ntd Hydro::ntd = Number of digits to represent Hydro::ntimes
     * @param[in] peel_onion "true" in analysis mode with spherical symmetry
     * @param[in] gol Reference to the current Goal object
     */
    void do_patch(Progress *parent, const IntPair &patch,
                  const Grid &g, const Mesh &m, const Database &d,
                  const Table &tbl,
                  const size_t it, const double t, const double dt,
                  const int ntd, const bool peel_onion, Goal &gol);

    /**
     * @brief Transport all Rays for all spatial patches of *this Detector
     * @param[in] parent Pointer to the previous level's Progress object
     * @param[in] g Reference to the current Grid object
     * @param[in] m Reference to the current Mesh object
     * @param[in] d Reference to the current Database object
     * @param[in] tbl Reference to the current Table object
     * @param[in] it Current time step index
     * @param[in] t Current time instant (seconds)
     * @param[in] dt Current time step size (seconds)
     * @param[in] ntd Hydro::ntd = Number of digits to represent Hydro::ntimes
     * @param[in] gol Reference to the current Goal object
     */
    void do_patches(Progress *parent,
                    const Grid &g, const Mesh &m, const Database &d,
                    const Table &tbl,
                    const size_t it, const double t, const double dt,
                    const int ntd, Goal &gol);

    /**
     * @brief Transport a Ray in analysis mode and/or evaluate fitness
     * @param[in] ndim Hydro::ndim = number of analysis cases per Cell
     * @param[in] g Reference to the current Grid object
     * @param[in] m Reference to the current Mesh object
     * @param[in] d Reference to the current Database object
     * @param[in] tbl Reference to the current Table object
     * @param[in] jt Current case index
     * @param[in] t Current time instant (inactive)
     * @param[in] dt Current time step size (inactive)
     * @param[in] ntd Hydro::ntd = Number of digits to represent Hydro::ntimes
     * @param[in] gol Reference to the current Goal object
     */
    void evaluate(const std::vector<size_t> &ndim,
                  const Grid &g, const Mesh &m, const Database &d,
                  const Table &tbl, const size_t jt, const double t,
                  const double dt, const int ntd, Goal &gol);

    /**
     * @brief Converter of patch ID to string
     * @param[in] patch Spatial element within *this Detector
     * @return String intended for file header
     */
    std::string patch_string(const IntPair &patch) const;

    /**
     * @brief Converter of patch ID to string
     * @param[in] patch Spatial element within *this Detector
     * @return String intended for file name
     */
    std::string patch_fname(const IntPair &patch) const;

    /**
     * @brief Converter of Ray direction ID to string
     * @param[in] direction Ray direction indices
     * @return String intended for file header
     */
    std::string omega_string(const IntPair &direction) const;

    /**
     * @brief Converter of Ray direction ID to string
     * @param[in] direction Ray direction indices
     * @return String intended for file name
     */
    std::string omega_fname(const IntPair &direction) const;

    /**
     * @brief Print broadened spectrum to file, except in "analysis" mode
     * @param[in] parent Pointer to the previous level's Progress object
     * @param[in] gol Goal object to access mode ("analysis", or not)
     * @param[in] h Reference to Hydro object
     */
    void yt_to_files(Progress *parent, Goal &gol, const Hydro &h);


//private:

    /// Number of Grid points
    static constexpr size_t NPT = 4;

    /// Frequency of Progress prints for loop over patches
    size_t freq_patch;

    /// Frequency of Progress prints for individual Rays
    size_t freq_Ray;

    /// Frequency of Progress prints for raytracing
    size_t freq_trace;

    /// *this Detector's name
    std::string dname;

    /// Path to output files for *this Detector
    std::string path;

    /// "none", "spherical", ("cylindrical" to be added)
    std::string symmetry;

    /// *this Detector's label within Diagnostics
    int my_id;

    /// Central point of *this Detector
    Vector3d rc;

    /// Lower-leftmost Ray contact point
    Vector3d ro;

    /// Axes half-vector (rx is assumed to be perpendicular to ry)
    Vector3d rx;

    /// Axes half-vector (rx is assumed to be perpendicular to ry)
    Vector3d ry;

    /// Unit vector for *this plane (ex, ey), normal (ez)
    Vector3d ex;

    /// Unit vector for *this plane (ex, ey), normal (ez)
    Vector3d ey;

    /// Unit vector for *this plane (ex, ey), normal (ez)
    Vector3d ez;

    /// Unit vector for Ray bundles
    Vector3d bx;

    /// Unit vector for Ray bundles
    Vector3d by;

    /// Unit vector for Ray bundles
    Vector3d bz;

    /// Row of the transformation matrix (Detector::local_to_global conversion)
    Vector3d xr;

    /// Row of the transformation matrix (Detector::local_to_global conversion)
    Vector3d yr;

    /// Row of the transformation matrix (Detector::local_to_global conversion)
    Vector3d zr;

    /// Ray spacing (cm) along each dimension ( > 0)
    double dx;

    /// Ray spacing (cm) along each dimension ( > 0)
    double dy;

    /// Patch area (cm2)
    double da;

    /// Neighboring Ray spacing vector
    Vector3d ux;

    /// Neighboring Ray spacing vector
    Vector3d uy;

    /// Actual size of ArrDbl spectrum
    size_t nhv;

    /// Actual photon energy grid (eV)
    std::vector<double> hv;

    /// Actual photon energy range: lower limit (eV)
    double hvmin;

    /// Actual photon energy range: upper limit (eV)
    double hvmax;

    /// Index for hvmin within hv_grid.txt
    size_t jmin;

    /// Index for hvmax within hv_grid.txt
    size_t jmax;

    /// Broadening half-width from instrumental resolution
    double fwhm;

    /// Backlighter value type: "flat" or "blackbody"
    std::string back_type;

    /// Backlighter file name
    std::string back_fname;

    /// "flat" backlighter (W/cm2/sr/eV); or temperature of "blackbody" (eV)
    double back_value;

    /// Backlighter values (W/cm2/sr/eV)
    std::vector<double> yback;

    /// Backlighter temperature time history values (eV)
    std::vector<double> trad;

    /// Tracking of partial results along *this Detector's Rays
    bool tracking;

    /// Turn on/off writing spectra from each Ray
    bool write_Ray;

    /// Number of intervals along x dimension
    size_t nx;

    /// Number of intervals along y dimension
    size_t ny;

    /// Number of digits needed to label nx
    int nxd;

    /// Number of digits needed to label ny
    int nyd;

    /// Pointing of this Detector
    Vector3d pc;

    /// Ray bundle's half angle (radians)
    double theta_max;

    /// Number of intervals in polar direction
    size_t ntheta;

    /// Minimum number of intervals in azimuthal direction
    size_t nphi;

    /// Number of digits needed to label ntheta
    int nthetad;

    /// Number of digits needed to label nphi
    int nphid;

    /// Spacing (radians) in polar direction
    double dtheta;

    /// Half Detector::dtheta
    double dtheta2;

    /// Corner-defining Nodes
    Grid gdet;

    /// Detector's surface
    Polygon p;

    /// Space-resolved, time-resolved spectra
    SpecPatch yp;

    /// Space-integrated, time-resolved spectrum
    ArrDbl ys;
};

//-----------------------------------------------------------------------------

/**
 * @brief Converter of time ID to string
 * @param[in] it Current time step index
 * @param[in] ntd Hydro::ntd = Number of digits to represent Hydro::ntimes
 * @param[in] t Current time instant (seconds)
 * @return String intended for file header
 */
std::string time_string(const size_t it, const int ntd, const double t);

/**
 * @brief Converter of time ID to string
 * @param[in] it Current time step index
 * @param[in] ntd Hydro::ntd = Number of digits to represent Hydro::ntimes
 * @return String intended for file name
 */
std::string time_fname(const size_t it, const int ntd);

/**
 * @brief Send string version of Detector to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o Detector object
 * @return Reference to output stream
 */
std::ostream & operator << (std::ostream &ost, const Detector &o);

//-----------------------------------------------------------------------------

#endif  // LANL_ASC_PEM_DETECTOR_H_
