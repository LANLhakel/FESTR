#ifndef LANL_ASC_PEM_NODE_H_
#define LANL_ASC_PEM_NODE_H_

/**
 * @file Node.h
 * @brief Grid Node
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 19 November 2014\n
 * Last modified on 28 January 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <Vector3d.h>

#include <iostream>
#include <string>

//-----------------------------------------------------------------------------

/// Grid Node
class Node
{
public:

    /// Default constructor
    Node();

    /**
     * @brief Parametrized constructor
     * @param[in] iin Initializes Node id (Node::i)
     * @param[in] rin Initializes Node position (Node::r)
     */
    Node(const size_t iin, const Vector3d &rin);

    /**
     * @brief Parametrized constructor
     * @param[in] iin Initializes Node id (Node::i)
     * @param[in] rin Initializes Node position (Node::r)
     * @param[in] vin Initializes Node velocity (Node::v)
     */
    Node(const size_t iin, const Vector3d &rin, const Vector3d &vin);

    /**
     * @brief Setter for Node id (Node::i)
     * @param[in] iin Node id
     */
    void seti(const size_t iin);
    
    /**
     * @brief Getter for Node id (Node::i)
     * @return Node id
     */
    size_t geti() const;
    
    /**
     * @brief Setter for Node position (Node::r)
     * @param[in] rin Node position
     */
    void setr(const Vector3d &rin);

    /**
     * @brief Getter for Node position (Node::r)
     * @return Node position
     */
    Vector3d getr() const;

    /**
     * @brief Setter for Node velocity (Node::v)
     * @param[in] vin Node velocity
     */
    void setv(const Vector3d &vin);
    
    /**
     * @brief Getter for Node velocity (Node::v)
     * @return Node velocity
     */
    Vector3d getv() const;

    /**
     * @brief Absolute difference between two Nodes
     * @param[in] o Node
     * @return See Definition
     */
    double abs_diff(const Node &o) const;

    /**
     * @brief String representation of a Node object
     * @return String representation of *this
     */
    std::string to_string() const;


private:

    /// Node id
    size_t i;

    /// Node position
    Vector3d r;

    /// Node velocity
    Vector3d v;
};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of Node to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o Node object
 * @return Reference to output stream
 */
std::ostream & operator << (std::ostream &ost, const Node &o);

//-----------------------------------------------------------------------------

#endif  // LANL_ASC_PEM_NODE_H
