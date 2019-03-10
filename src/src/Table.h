#ifndef TABLE_H
#define TABLE_H

/**
 * @file Table.h
 * @brief Atomic data for materials
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 9 January 2015\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <string>
#include <map>

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
    TableData(void): z(0), a(0.0), f("") {}

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
typedef std::map< std::string, TableData > TableMap;

//-----------------------------------------------------------------------------

/// Atomic data for materials
class Table
{
private:

    /// Maps material name (key) to TableData (value)
    TableMap d;

public:

    /// Default constructor
    Table(void);

    /**
     * @brief Parametrized constructor
     * @param[in] hydro_path Path to directory containing Hydro data
     * @param[in] table_path Path to directory containing Table data
     * @param[in] table_fname Name of file containing Table data
     */
    Table(const std::string &hydro_path, const std::string &table_path,
          const std::string &table_fname);

    /// Destructor
    ~Table(void);

    /// Clears Table
    void clear(void);

    /**
     * @brief Getter for Table size
     * @return Number of materials in Table
     */
    size_t size(void) const;

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
};

//-----------------------------------------------------------------------------

#endif // TABLE_H
