#ifndef LANL_ASC_PEM_GOAL_H_
#define LANL_ASC_PEM_GOAL_H_

/**
 * @file Goal.h
 * @brief A collection of Objective objects
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 28 June 2015\n
 * Last modified on 8 October 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <Mesh.h>
#include <Objective.h>

#include <string>
#include <vector>

//-----------------------------------------------------------------------------

/// A collection of Objective objects used in analysis mode for fitting
class Goal
{
public:

    /// Default constructor
    Goal();

    /**
     * @brief Parametrized constructor
     * @param[in] analysis_in Initializes Objective::analysis
     * @param[in] goal_path Initializes Objective::path
     */
    Goal(const bool analysis_in, const std::string &goal_path);

    /**
     * @brief Getter for the pointer to the i-th Objective (Goal::obj)
     * @param[in] i Index
     * @return Pointer to i-th Objective object
     */
    ObjectivePtr get_objective(const size_t i) const;

    /**
     * @brief Getter for the number of Objectives (Goal::n)
     * @return Number of Objectives in *this Goal
     */
    size_t size() const;

    /**
     * @brief Getter for the analysis mode (Goal::analysis)
     * @return "true" or "false
     */
    bool get_analysis() const;

    /**
     * @brief Setter for the analysis mode (Goal::analysis)
     * @param[in] a Analysis mode: "true" or "false
     */
    void set_analysis(const bool a);

    /**
     * @brief String representation of a Goal object
     * @return String representation of *this
     */
    std::string to_string() const;

    /**
     * @brief Getter for the name of the i-th Objective (Objective::oname)
     * @param[in] i Index
     * @return The name of the i-th Objective
     */
    std::string get_name(const size_t i) const;

    /**
     * @brief Getter for the index of the named Objective within *this Goal
     * @param[in] s Name of the Objective
     * @return Index of the Objective; or Goal::n, if not found
     */
    size_t get_index(const std::string &s) const;

    /**
     * @brief Getter for the fitness of the i-th Objective (Objective::fitness)
     * @param[in] i Index
     * @return The fitness of the current best case of the i-th Objective
     */
    double get_fitness_at(const size_t i) const;

    /**
     * @brief Evaluate the fitness of data a for the named Objective
     * @param[in] s Name of the Objective
     * @param[in] a Data to be evaluated
     *            (must support "double operator [](size_t)" method)
     */
    template<typename T>
    void fit_eval(const std::string &s, const T &a)
    {
        size_t i = get_index(s);
        if (i < n) fitness.at(i) = obj.at(i)->get_fitness(a, a.size());
    }

    /**
     * @brief Calculate scalarized fitness for *this Goal
     * @return Average of all current fitnesses within *this Goal
     */
    double get_fitness() const;

    /**
     * @brief Getter for Goal::best_fitness
     * @return Best fitness for *this Goal
     */
    double get_best_fitness() const;

    /**
     * @brief Setter for Goal::best_case (used if symmetry == "spherical")
     * @param[in] i Index of the best case
     */
    void set_best_case(const size_t i);

    /**
     * @brief Getter for Goal::best_case
     * @return Index of the best case
     */
    size_t get_best_case() const;

    /**
     * @brief Check if i-th case is best and update Goal object accordingly
     * @param[in] i Index of the candidate case
     */
    void update_best(const size_t i);

    /**
     * @brief Getter for scale factor of a named Objective
     * @param[in] s Name of the Objective
     * @return Scale factor of the best case within Objective named s;
     *         or 1.0, if Objective s is not found within *this Goal
     */
    double get_best_scale(const std::string &s) const;


private:

    /// Initial (very poor) fitness
    static const double BIG;
    
    /// Path to *this Goal description
    std::string path;

    /// List of Objectives
    std::vector<ObjectivePtr> obj;

    /// "true" in analysis, "false" in postprocessing mode
    bool analysis;

    /// Currently best fitnesses
    std::vector<double> fitness;

    /// Currently best scalarized fitness
    double best_fitness;

    /// ID of the currently best case
    size_t best_case;

    /// Number of Objectives in *this Goal
    size_t n;
};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of Goal to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o Goal object
 * @return Reference to output stream
 */
std::ostream & operator << (std::ostream &ost, const Goal &o);

//-----------------------------------------------------------------------------

#endif  // LANL_ASC_PEM_GOAL_H_
