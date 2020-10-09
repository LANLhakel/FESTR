/**
 * @file load_Faces.inc
 * @brief Include file: load Face definitions from a geometry file
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 8 January 2015\n
 * Last modified on 26 February 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

/*=============================================================================

#included in Surface.cpp, Zone.cpp

Load Faces from an open ifstream geometry.

=============================================================================*/

for (size_t i = 0; i < nfaces; ++i)
{
    std::string face_type;
    geometry >> face_type;
    face.push_back(FaceFactory::make_face(face_type, geometry));
}

//  end load_Faces.inc
