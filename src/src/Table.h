#ifndef LANL_ASC_PEM_TABLE_H_
#define LANL_ASC_PEM_TABLE_H_

/**
 * @file Table.h
 * @brief Atomic data for materials
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 9 January 2015\n
 * Last modified on 29 September 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <map>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------

/// Encapsulates material info for Table
struct TableData
{
    /// Nuclear charge
    int z;

    /// Atomic weight
    double a;

    /// File handle
    std::string f;

    /// Default constructor
    TableData(): z(0), a(0.0), f("") {}

    /// Copy constructor
    TableData(const TableData &t): z(t.z), a(t.a), f(t.f) {}

    /**
     * @brief Parametrized constructor
     * @param[in] zin Initializes nuclear charge (TableData::z)
     * @param[in] ain Initializes atomic weight (TableData::a)
     * @param[in] fin Initializes file handle (TableData::f)
     */
    TableData(const int zin, const double ain, const std::string fin):
        z(zin), a(ain), f(fin) {}
};

//-----------------------------------------------------------------------------

/// Maps material name (key) to TableData (value)
typedef std::map<std::string, TableData> TableMap;

//-----------------------------------------------------------------------------

/// Atomic data for materials
class Table
{
public:

    /// Default constructor
    Table();

    /**
     * @brief Parametrized constructor
     * @param[in] hydro_path Path to directory containing Hydro data
     * @param[in] table_path Path to directory containing Table data
     * @param[in] table_fname Name of file containing Table data
     */
    Table(const std::string &hydro_path, const std::string &table_path,
          const std::string &table_fname);

    /// Clears Table
    void clear();

    /**
     * @brief Getter for Table size
     * @return Number of materials in Table
     */
    size_t size() const;

    /**
     * @brief Getter for nuclear charge
     * @param[in] s Name of material (material ID)
     * @return Nuclear charge of material\n
     *         throws an exception, if material is not in the Table
     */
    int get_Z(const std::string s) const;

    /**
     * @brief Getter for atomic weight
     * @param[in] s Name of material (material ID)
     * @return Atomic weight of material\n
     *         throws an exception, if material is not in the Table
     */
    double get_A(const std::string s) const;

    /**
     * @brief Getter for neutron number
     * @param[in] s Name of material (material ID)
     * @return Neutron number of material\n
     *         throws an exception, if material is not in the Table
     */
    int get_N(const std::string s) const;

    /**
     * @brief Getter for file handle
     * @param[in] s Name of material (material ID)
     * @return File handle for material\n
     *         throws an exception, if material is not in the Table
     */
    std::string get_F(const std::string s) const;

    /**
     * @brief Convert atom abundances to normalized mass fractions
     * @param[in] mat Materials
     * @param[in] a Atom abundances
     * @return Mass fractions normalized to add up to 1
     */
    std::vector<double> atom_to_mass(const std::vector<std::string> &mat,
                                     const std::vector<double> &a) const;

    /**
     * @brief Convert mass abundances to normalized atom fractions
     * @param[in] mat Materials
     * @param[in] m Mass abundances
     * @return Atom fractions normalized to add up to 1
     */
    std::vector<double> mass_to_atom(const std::vector<std::string> &mat,
                                     const std::vector<double> &m) const;

    /**
     * @brief Return a sorted (ascending) vector of atomic numbers
     * @return Atomic numbers of elements present in *this Table
     */
    std::vector<int> get_elements() const;

private:

    /// Maps material name (key) to TableData (value)
    TableMap d;
};

//-----------------------------------------------------------------------------

#endif  // LANL_ASC_PEM_TABLE_H_
