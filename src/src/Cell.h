#ifndef CELL_H
#define CELL_H

/**
 * @file Cell.h
 * @brief Class Zone reduced to hold only materials' search grids for analysis
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 4 July 2015\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <vector>
#include <string>
#include <map>
#include <fstream>

//-----------------------------------------------------------------------------

/// Maps material name (key) to density grid (value)
typedef std::map< std::string, std::vector<double> > FpopMap;

//-----------------------------------------------------------------------------

/// Encapsulates material conditions for a single Zone / Cell
struct CellEOS
{
    /// Electron temperature (eV)
    double te;

    /// Radiation temperature (eV)
    double tr;

    /// Number of materials in the Zone
    unsigned short int nmat;

    /// Material IDs
    std::vector<std::string> mat;

    /// Material densities (Zone::np = 1 in this context)
    std::vector<double> fp;

    /// Default constructor
    CellEOS(): te(-1.0), tr(-1.0), nmat(0), mat(), fp() {}

};

//-----------------------------------------------------------------------------

/// Class Zone reduced to hold only materials' search grids for analysis
class Cell
{
private:

    /// Density units (e.g. "ions/cm3", "g/cm3" - currently "none" and unused)
    std::string np_unit;


    // Geometry (read from "mesh_0.txt" file)

    /// Unique ID of *this Cell on the Mesh
    size_t my_id;


    // Materials (search ranges for EOS data, read from "time_0.txt" file)

    /// Electron temperature grid: lower bound (eV)
    double telow;

    /// Electron temperature grid: upper bound (eV)
    double tehigh;

    /// Radiation temperature grid: lower bound (eV)
    double trlow;

    /// Radiation temperature grid: upper bound (eV)
    double trhigh;

    /// Number of materials in *this Cell
    unsigned short int nmat;

    /// Material IDs
    std::vector<std::string> mat;

    /** @brief Lower bound of total particle number density grid (1/cm3), or,
     *         \n total mass density (g/cm3) if using OPLIB via TOPS
     */
    std::vector<double> fplow;

    /** @brief Upper bound of total particle number density grid (1/cm3), or,
     *         \n total mass density (g/cm3) if using OPLIB via TOPS
     */
    std::vector<double> fphigh;

    /// Number of electron temperature grid points
    size_t nte;

    /// Number of radiation temperature grid points
    size_t ntr;

    /// Number of search cases for each material in *this Cell
    std::vector<size_t> nfp;

    /// Number of te, tr, fp search cases *this Cell (nall.size() == 3)
    std::vector<size_t> nall; // nall = (nte, ntr, Product(nfp's) )


    // Grid interpolation modes

    /// Electron temperature grid interpolation mode: "lin" or "log"
    std::string gte;

    /// Radiation temperature grid interpolation mode: "lin" or "log"
    std::string gtr;

    /// Total density grid interpolation mode: "lin" or "log"
    std::string gnp;

    /// Individual material density grids interpolation modes: "lin" or "log"
    std::vector<std::string> gfp;

    /// Electron temperature (eV) search grid for *this Cell
    std::vector<double> tegrid;

    /// Radiation temperature (eV) search grid for *this Cell
    std::vector<double> trgrid;

    /// Density search grid for *this Cell (density == 0 is always included)
    FpopMap fpgrid;


public:

    /// Default constructor
    Cell(void);

    /**
     * @brief Parametrized constructor: sets Cell ID within its Mesh
     * @param[in] my_id_in Initializes Cell::my_id
     */
    explicit Cell(const size_t my_id_in);

    /**
     * @brief Parametrized constructor: loads search grid info from file
     * @param[in] material Input stream for material data file
     */
    explicit Cell(std::ifstream &material);

    /// Destructor
    ~Cell(void);

    /**
     * @brief Setter for the Cell ID in its Mesh (Cell::my_id)
     * @param[in] my_id_in Cell index
     */
    void set_id(const size_t my_id_in);

    /**
     * @brief Getter for the Cell ID in its Mesh (Cell::my_id)
     * @return Cell index
     */
    size_t get_id(void) const;

    /**
     * @brief String representation of a Cell object
     * @return String representation of *this
     */
    std::string to_string(void) const;

    /**
     * @brief Getter for Cell::nte
     * @return Number of electron temperature grid points
     */
    size_t get_nte(void) const;

    /**
     * @brief Getter for Cell::tegrid
     * @return Electron temperature grid points (eV)
     */
    std::vector<double> get_tegrid(void) const;

    /**
     * @brief Getter for Cell::ntr
     * @return Number of radiation temperature grid points
     */
    size_t get_ntr(void) const;

    /**
     * @brief Getter for Cell::trgrid
     * @return Radiation temperature grid points (eV)
     */
    std::vector<double> get_trgrid(void) const;

    /**
     * @brief Getter for Cell::nmat
     * @return Number of materials in *this Cell
     */
    unsigned short int get_nmat(void) const;

    /**
     * @brief Getter for Cell::nfp
     * @return Number of search cases for each material in *this Cell
     */
    std::vector<size_t> get_nfp(void) const;

    /**
     * @brief Getter for Cell::fpgrid
     * @return Density search grid for *this Cell
     */
    FpopMap get_fpgrid(void) const;

    /**
     * @brief Retrieves Cell material conditions
     * @param[in] ite Electron temperature search case index
     * @param[in] itr Radiation temperature search case index
     * @param[in] ifp Material densities global search case index
     * @return Temperatures and densities encapsulated in a CellEOS object
     */
    CellEOS get_eos(const size_t ite, const size_t itr, const size_t ifp);

    /**
     * @brief Getter for Cell::nall
     * @return Number of te, tr, fp search cases *this Cell,
     *         (nte, ntr, Product(nfp's)
     */
    std::vector<size_t> get_nall(void) const;

    /**
     * @brief Retrieves Cell material conditions
     * @param[in] i Material temperatures/densities global search case index
     * @return Temperatures and densities encapsulated in a CellEOS object
     */
    CellEOS get_cell_eos(const size_t i);

    /**
     * @brief Calculates Product(nall's)
     * @return Total number of search cases for *this Cell
     */
    size_t get_ncases(void) const;

};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of Cell to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o Cell object
 * @return Reference to output stream
 */
std::ostream & operator << (std::ostream &ost, const Cell &o);

//-----------------------------------------------------------------------------

#endif // CELL_H
