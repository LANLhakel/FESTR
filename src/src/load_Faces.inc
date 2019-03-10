/**
 * @file load_Faces.inc
 * @brief Include file: load Face definitions from a geometry file
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 8 January 2015\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

/*=============================================================================

#included in Surface.cpp, Zone.cpp

Load Faces from an open ifstream geometry.

=============================================================================*/

std::string face_type;
Face *f;
for (size_t i = 0; i < nfaces; ++i)
{
    geometry >> face_type;
    if (face_type == "Polygon") f = new Polygon(geometry);
    else if (face_type == "Sphere") f = new Sphere(geometry);
    else if (face_type == "Cone") f = new Cone(geometry);
    else if (face_type == "Surface") f = new Surface(geometry);
    else
    {
        std::cerr << "Error: face_type not recognized "
                  << "in load_Faces.cpp" << std::endl;
        exit(EXIT_FAILURE);
    }
    face.push_back(f);
}

// end load_Faces.inc
