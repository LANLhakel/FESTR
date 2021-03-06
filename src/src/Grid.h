#ifndef LANL_ASC_PEM_GRID_H_
#define LANL_ASC_PEM_GRID_H_

/**
 * @file Grid.h
 * @brief Grid of Node objects
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 21 November 2014\n
 * Last modified on 28 January 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <Node.h>

#include <iostream>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------

/// Grid of Node objects
class Grid
{
public:

    /// Default constructor
    Grid();

    /**
     * @brief Parametrized constructor: loads a Grid of Nodes from a file
     * @param[in] path Path to the input file
     * @param[in] tlabel Time-step label used in the name of the input file
     */
    Grid(const std::string &path, const std::string &tlabel);

    /// Removes all Nodes from *this Grid
    void clear();

    /**
     * @brief Adds a new Node at the end of *this Grid
     * @param[in] nin New Node
     */
    void add_node(const Node &nin);
    
    /**
     * @brief Adds a new Node at the end of *this Grid
     * @param[in] nin New Node
     */
    void add_node(Node &&nin);
    
    /**
     * @brief Getter for the Node at index i
     * @param[in] i Node index
     * @return Node at index i
     */
    Node get_node(const size_t i) const;

    /**
     * @brief Replaces the Node at the location encoded in the new Node
     * @param[in] nin New Node
     */
    void replace_node(const Node &nin);

    /**
     * @brief Getter for number of Nodes
     * @return Size of *this Grid
     */
    size_t size() const;

    /**
     * @brief Absolute difference between two Grids
     * @param[in] o Grid
     * @return See Definition
     */
    double abs_diff(const Grid &o) const;

    /**
     * @brief Loads a Grid of Nodes from a file
     * @param[in] path Path to the input file
     * @param[in] tlabel Time-step label used in the name of the input file
     */
    void load(const std::string &path, const std::string &tlabel);

    /**
     * @brief String representation of a Grid object
     * @return String representation of *this
     */
    std::string to_string() const;


private:

    /// Array of Nodes
    std::vector<Node> node;

    /// Number of Nodes in *this Grid
    size_t num_nodes;
};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of Grid to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o Grid object
 * @return Reference to output stream
 */
std::ostream & operator << (std::ostream &ost, const Grid &o);

//-----------------------------------------------------------------------------

#endif  // LANL_ASC_PEM_GRID_H_
