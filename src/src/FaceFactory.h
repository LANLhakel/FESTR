#ifndef LANL_ASC_PEM_FACEFACTORY_H_
#define LANL_ASC_PEM_FACEFACTORY_H_

/**
 * @file FaceFactory.h
 * @brief Factory for creating objects derived from abstract class Face
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 24 February 2020\n
 * Last modified on 24 February 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

#include <fstream>
#include <memory>
#include <string>

//-----------------------------------------------------------------------------

class Face;
typedef std::shared_ptr<Face> FacePtr;

//-----------------------------------------------------------------------------

/// Factory for creating objects derived from abstract class Face
struct FaceFactory
{
    /// Construct an object derived from class Face
    static FacePtr make_face(const std::string &face_type,
                             std::ifstream &geometry);
};

//-----------------------------------------------------------------------------

#endif  // LANL_ASC_PEM_FACEFACTORY_H_
