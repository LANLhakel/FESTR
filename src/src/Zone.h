#ifndef ZONE_H
#define ZONE_H

/**
 * @file Zone.h
 * @brief Spatial zone, defined by a list bounding Face objects
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 8 December 2014\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include "Face.h"
#include "Database.h"
#include "ArrDbl.h"

//-----------------------------------------------------------------------------

/// Spatial zone, defined by a list bounding Face objects
class Zone
{
private:
    // Geometry (read from "mesh_*" files)

    /// Unique ID of *this Zone on the Mesh
    size_t my_id;

    /// List of pointers to Face objects defining *this Zone
    std::vector<const Face *> face; // copy ctor and operator = may be needed


    // Materials (EOS data, read from "time_*" files)

    /// Electron temperature (eV)
    double te;

    /// Radiation temperature (eV)
    double tr;

    /// Total particle number density (particles/cm3)
    double np;

    /// Number of materials in *this Zone
    unsigned short int nmat;

    /// Material IDs
    std::vector<std::string> mat;

    /// Fractional populations
    std::vector<double> fp;

    /// Electron number density (el./cm3) from charge neutrality constraint
    double ne;


    // Arrays only to be used in 1-D geometry to speed up the calculation
    // by computing optical data once, and then saving/retrieving them

    /// Monochromatic emissivity ( W / cm3 / sr / eV )
    ArrDbl emis;

    /// Monochromatic absorption coefficient ( 1 / cm )
    ArrDbl absp;

    /// Monochromatic scattering coefficient ( 1 / cm )
    ArrDbl scat;


public:

    /// ID of the bounding Zone
    static const size_t BOUNDING_ZONE;

    /// Default constructor
    Zone(void);

    /**
     * @brief Parametrized constructor: sets Zone ID within its Mesh
     * @param[in] my_id_in Initializes Zone::my_id
     */
    explicit Zone(const size_t my_id_in);

    /**
     * @brief Parametrized constructor: loads geometry/material info from files
     * @param[in] geometry Input stream for geometry data file
     * @param[in] material Input stream for material data file
     */
    Zone(std::ifstream &geometry, std::ifstream &material);

    /// Destructor
    ~Zone(void);

    /// Wipes out all data from *this Zone
    void clear(void);

    /**
     * @brief Setter for the Zone ID in its Mesh (Zone::my_id)
     * @param[in] my_id_in Zone index
     */
    void set_id(const size_t my_id_in);

    /**
     * @brief Getter for the Zone ID in its Mesh (Zone::my_id)
     * @return Zone index
     */
    size_t get_id(void) const;

    /**
     * @brief Adds Face to *this Zone (Zone::face)
     * @param[in] f Face pointer
     */
    void add_face(const Face * const f);

    /**
     * @brief Getter for the i-th Face within *this Zone (Zone::face)
     * @param[in] i Face index
     * @return Face pointer
     */
    const Face * get_face(const short int i) const;

    /**
     * @brief Setter for the electron number density (Zone::ne)
     * @param[in] ne_in Electron number density (electrons/cm3)
     */
    void set_ne(const double ne_in);

    /**
     * @brief Getter for the electron number density (Zone::ne)
     * @return Electron number density (electrons/cm3) in *this Zone
     */
    double get_ne(void) const;

    /**
     * @brief Setter for the electron temperature (Zone::te)
     * @param[in] te_in Electron temperature (eV)
     */
    void set_te(const double te_in);

    /**
     * @brief Getter for the electron temperature (Zone::te)
     * @return Electron temperature (eV) in *this Zone
     */
    double get_te(void) const;

    /**
     * @brief Setter for the radiation temperature (Zone::tr)
     * @param[in] tr_in Radiation temperature (eV)
     */
    void set_tr(const double tr_in);

    /**
     * @brief Getter for the radiation temperature (Zone::tr)
     * @return Radiation temperature (eV)
     */
    double get_tr(void) const;

    /**
     * @brief Setter for total density (Zone::np)
     * @param[in] np_in Total density (ions/cm3)
     */
    void set_np(const double np_in);

    /**
     * @brief Getter for total density (Zone::np)
     * @return Total density (ions/cm3)
     */
    double get_np(void) const;

    /**
     * @brief Setter for number of materials (Zone::nmat)
     * @param[in] nmat_in Number of materials
     */
    void set_nmat(unsigned short int nmat_in);

    /**
     * @brief Getter for number of materials (Zone::nmat)
     * @return Number of materials
     */
    unsigned short int get_nmat(void) const;

    /**
     * @brief Setter for material IDs (Zone::mat)
     * @param[in] mat_in Material IDs
     */
    void set_mat(const std::vector<std::string> &mat_in);

    /**
     * @brief Getter for a specific material ID (Zone::mat)
     * @param[in] i Material's integer index within *this Zone
     * @return Material ID
     */
    std::string mat_at(const unsigned short int i) const;

    /**
     * @brief Getter for material IDs (Zone::mat)
     * @return Material IDs
     */
    const std::vector<std::string> &get_mat(void) const;

    /**
     * @brief Setter for material fractions (Zone::fp)
     * @param[in] fp_in Material fractions (atomic)
     */
    void set_fp(const std::vector<double> &fp_in);

    /**
     * @brief Getter for the fraction of a specific material (Zone::fp)
     * @param[in] i Material's integer index within *this Zone
     * @return Material fraction (atomic)
     */
    double fp_at(const unsigned short int i) const;

    /**
     * @brief Getter for material fractions (Zone::fp)
     * @return Material fractions (atomic)
     */
    const std::vector<double> &get_fp(void) const;

    /**
     * @brief Getter for the number of Face objects for *this Zone
     * @return Number of Face objects for *this Zone
     */
    size_t size(void) const;

    /**
     * @brief Calculates the hit-point where a Ray enters *this Zone
     * @param[in] g Grid of Node objects
     * @param[in] p Ray exit point (Ray paths are traced backwards)
     * @param[in] u Reverse of Ray velocity's Vector3d through *this Zone
     * @param[in] fid FaceID of the Face through which Ray exits *this Zone
     * @return RetIntercept structure with the info on the next intercept
     */
    RetIntercept hit(const Grid &g, const Vector3d &p, const Vector3d &u,
                     const FaceID &fid) const;

    /**
     * @brief String representation of a Zone object
     * @return String representation of *this
     */
    std::string to_string(void) const;

    /**
     * @brief Loads geometry (Face shapes and sizes) info from input file;
     *        \n assumes ::find_word (geometry, "Zone") has already
     *        been called
     * @param[in] geometry Input stream for geometry data file
     */
    void load_geo(std::ifstream &geometry);

    /**
     * @brief Loads material info (temperatures, densities) from input file;
     *        \n assumes Zone::load_geo (geometry) has already been called,
     *        \n assumes ::find_word (material, "Zone") has already
     *        been called
     * @param[in] material Input stream for material data file
     */
    void load_mat(std::ifstream &material);

    /**
     * @brief Builds mixed monochromatic optical data for *this Zone;
     *        \n if symmetry != "none", also either stores newly computed data
     *        \n (Zone::emis, Zone::absp, Zone::scat) or retrieves them.
     *        \n Assumes Zone::load_mat (material) has already been called
     * @param[in] d Database
     * @param[in] tbl Table of materials
     * @param[in,out] ite Electron temperature integer index from Database
     * @param[in,out] itr Radiation temperature integer index from Database
     * @param[in,out] ine Electron density integer index from Database
     * @param[in] symmetry For example, "spherical", "none"
     * @param[in] ix Component of the spatial patch ID from Detector
     * @param[in] analysis "true" or "false"
     * @param[in] jmin Lower index of the actual photon energy grid
     * @param[in] jmax Upper index of the actual photon energy grid
     * @param[in,out] em Mixed monochromatic emissivity ( W / cm3 / sr / eV )
     * @param[in,out] ab Mixed monochromatic absorption ( 1 / cm )
     * @param[in,out] sc Mixed monochromatic scattering ( 1 / cm )
     */
    void load_spectra(const Database &d, const Table &tbl,
                      size_t &ite, size_t &itr, size_t &ine,
                      const std::string &symmetry, const size_t ix,
                      const bool analysis,
                      const size_t jmin, const size_t jmax,
                      ArrDbl &em, ArrDbl &ab, ArrDbl &sc); // not const

    /**
     * @brief Full string representation of materials in *this Zone
     * @return Material info in the FESTR hydro input format (ASCII)
     */
    std::string mat_to_string_full(void) const;

    /**
     * @brief Abbreviated string representation of materials in *this Zone
     * @return Material info in simple columns (e.g., for plotting)
     */
    std::string mat_to_string_plot(void) const;

};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of Zone to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o Zone object
 * @return Reference to output stream
 */

std::ostream & operator << (std::ostream &ost, const Zone &o);

//-----------------------------------------------------------------------------

#endif // ZONE_H
