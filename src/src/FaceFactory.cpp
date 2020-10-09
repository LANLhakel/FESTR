/**
 * @file FaceFactory.cpp
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

#include <FaceFactory.h>

#include <Cone.h>
#include <Polygon.h>
#include <Sphere.h>
#include <Surface.h>

#include <cstdlib>

//-----------------------------------------------------------------------------

FacePtr FaceFactory::make_face(const std::string &face_type,
                               std::ifstream &geometry)
{
    if (face_type == "Polygon") return std::make_shared<Polygon>(geometry);
    else if (face_type == "Sphere") return std::make_shared<Sphere>(geometry);
    else if (face_type == "Cone") return std::make_shared<Cone>(geometry);
    else if (face_type == "Surface") return std::make_shared<Surface>(geometry);
    else
    {
        std::cerr << "Error: face_type not recognized "
                  << "in FaceFactory::make_face" << std::endl;
        exit(EXIT_FAILURE);
    }
}

//-----------------------------------------------------------------------------

//  end FaceFactory.cpp
