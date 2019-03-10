#ifndef OBJECTIVE_H
#define OBJECTIVE_H

/**
 * @file Objective.h
 * @brief Defines an objective to be matched by a calculation
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 24 June 2015\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <vector>
#include <string>
#include <stdexcept>
#include "utilities.h"

//-----------------------------------------------------------------------------

/// Defines an objective to be matched by a calculation
class Objective
{
private:

    /// Initial (very poor) fitness
    static const double BIG;

    /// *this Objective's name
    std::string oname;

    /// Path to data file for *this Objective
    std::string path;

    /// *this Objective's label within its Goal
    int my_id;

    /// *this Objective's overall weight within its Goal
    double weight;

    /// "true" if abscissae are present in the source data file for *this
    bool x_is_present;

    /// "true" if weights are present in the source data file for *this
    bool w_is_present;

    /// Abscissae
    std::vector<double> x;

    /// Data to be matched
    std::vector<double> y;

    /// Weights
    std::vector<double> w;

    /// Currently best fitness
    double best_fitness;

    /// ID of the currently best case
    size_t best_case;

    /// "true" if y-units are not absolute
    bool rescale;

    /// Scaling factor for the currently best case
    double best_scale;

public:

    /// Default constructor
    Objective(void);

    /**
     * @brief Parametrized constructor
     * @param[in] oname_in Initializes Objective::oname
     * @param[in] path_in Initializes Objective::path
     * @param[in] my_id_in Initializes Objective::my_id
     * @param[in] weight_in Initializes Objective::weight
     * @param[in] x_is_present_in Initializes Objective::x_is_present
     * @param[in] w_is_present_in Initializes Objective::w_is_present
     * @param[in] rescale_in Initializes Objective::rescale
     */
    Objective(const std::string &oname_in, const std::string &path_in,
              const int my_id_in, const double weight_in,
              const bool x_is_present_in, const bool w_is_present_in,
              const bool rescale_in);

    /// Destructor
    ~Objective(void);

    /**
     * @brief Absolute difference between two Objective objects
     * @param[in] o Objective
     * @return See Definition
     */
    double abs_diff(const Objective &o) const;

    /**
     * @brief String representation of an Objective object
     * @return String representation of *this
     */
    std::string to_string(void) const;

    /**
     * @brief Getter for Objective::oname
     * @return String
     */
    std::string get_oname(void) const;

    /**
     * @brief Getter for Objective::path
     * @return String
     */
    std::string get_path(void) const;

    /**
     * @brief Getter for Objective::my_id
     * @return Integer label
     */
    int get_my_id(void) const;

    /**
     * @brief Getter for Objective::weight
     * @return Double value
     */
    double get_weight(void) const;

    /**
     * @brief Getter for Objective::x_is_present in string form
     * @return String
     */
    std::string is_x_present(void) const;

    /**
     * @brief Getter for Objective::w_is_present in string form
     * @return String
     */
    std::string is_w_present(void) const;

    /**
     * @brief Getter for size of Objective::y
     * @return Integer
     */
    size_t get_size(void) const;

    /**
     * @brief Getter for Objective::x at index i
     * @param[in] i Array index
     * @return \f$x_i\f$
     */
    double get_x_at(const size_t i) const;

    /**
     * @brief Getter for Objective::y at index i
     * @param[in] i Array index
     * @return \f$y_i\f$
     */
    double get_y_at(const size_t i) const;

    /**
     * @brief Getter for Objective::w at index i
     * @param[in] i Array index
     * @return \f$w_i\f$
     */
    double get_w_at(const size_t i) const;

    /**
     * @brief Calculate a difference between an array and data stored by *this
     * @param[in] a Array (must support "double operator [](size_t)" method)
     * @param[in] n Number of elements in array a
     * @return \f$weight \times \sum_{i=0}^{n-1} | w_i (a_i - y_i) |\f$
     */
    template<typename T>
    double get_fabs(const T &a, const size_t n) const
    {
        #include "ObjectiveRangeCheck.inc"
        double s = 0.0;

        #ifdef OMPYES
        #pragma omp parallel for reduction (+:s)
        #endif
        for (size_t i = 0; i < n; ++i) {s += fabs( w[i] * (a[i] - y[i]) );}

        return weight * s;
    }

    /**
     * @brief Calculate chi-squared between an array and data stored by *this
     * @param[in] a Array (must support "double operator [](size_t)" method)
     * @param[in] n Number of elements in array a
     * @return \f$weight \times \sum_{i=0}^{n-1} w_i (a_i - y_i)^2\f$
     */
    template<typename T>
    double get_chi2(const T &a, const size_t n) const
    {
        #include "ObjectiveRangeCheck.inc"
        double s = 0.0;

        #ifdef OMPYES
        #pragma omp parallel for reduction (+:s)
        #endif
        for (size_t i = 0; i < n; ++i)
        {
            double d = a[i] - y[i];
            s += w[i] * pow(d, 2);
        }

        return weight * s;
    }

    /**
     * @brief Calculate fitness of an array for data stored by *this
     * @param[in] a Array (must support "double operator [](size_t)" method)
     * @param[in] n Number of elements in array a
     * @return \f$-\chi^2\f$
     */
    template<typename T>
    double get_fitness(const T &a, const size_t n) const
    {return -get_chi2(a, n);}

    /**
     * @brief Calculate fitness of an array for data stored by *this
     *        and update best case info, if the array is the best match yet
     * @param[in] a Array (must support "double operator [](size_t)" method)
     * @param[in] n Number of elements in array a
     * @param[in] j Index of the current analysis case
     */
    template<typename T>
    void update_best(const T &a, const size_t n, const size_t j)
    {
        double bf;
        double scale = 1.0;
        if (rescale) // scale "a", if data "y" units are unknown
        {
            double numerator = 0.0;
            double denominator = 0.0;

            #ifdef OMPYES
            #pragma omp parallel for reduction(+:numerator,denominator)
            #endif
            for (size_t i = 0; i < n; ++i)
            {
                numerator += w[i] * a[i] * y[i];
                denominator += w[i] * pow(a[i], 2);
            }

            scale = numerator / denominator;
            std::vector<double> ascaled(n);

            #include "ArrDblLoop.inc"
            {
                ascaled[i] = scale * a[i];
            }
            bf = get_fitness(ascaled, n);
        }
        else // no rescaling, if data "y" are given in absolute units
            bf = get_fitness(a, n);

        if (bf > best_fitness)
        {
            best_fitness = bf;
            best_case = j;
            if (rescale) best_scale = scale;
        }
    }

    /**
     * @brief Getter for Objective::best_fitness
     * @return Double value
     */
    double get_best_fitness(void) const;

    /**
     * @brief Getter for Objective::best_case
     * @return Integer index of the best case
     */
    size_t get_best_case(void) const;

    /**
     * @brief Getter for Objective::rescale
     * @return "true" or "false"
     */
    bool get_rescale(void) const;

    /**
     * @brief Getter for Objective::best_scale
     * @return Scale factor associated with the best case
     */
    double get_best_scale(void) const;
};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of Objective to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o Objective object
 * @return Reference to output stream
 */
std::ostream & operator << (std::ostream &ost, const Objective &o);

//-----------------------------------------------------------------------------

#endif // OBJECTIVE_H
