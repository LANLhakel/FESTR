/*=============================================================================
 
trace_Mesh.inc

#included in test_Ray.cpp

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 27 January 2015
Last modified on 27 February 2020

Copyright (c) 2015, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

CODE NAME:  FESTR, Version 0.9 (C15068)
Classification Review Number: LA-CC-15-045
Export Control Classification Number (ECCN): EAR99
B&R Code:  DP1516090

=============================================================================*/

#include <load_Table.inc>
std::string path(cnststr::PATH + "UniTest/Hydro1/");
std::string tlabel("1");
Grid g(path, tlabel);
Mesh m(path, tlabel);
Database d("none", cnststr::PATH + "UniTest/Dbase3/", false);
Vector3d r(12.968712349342937, 0.75, 0.5);
Vector3d v(-2.0, 0.0, 0.0);
std::string fname(cnststr::PATH + "UniTest/Output/partial");
std::string header("File name for zone\nRest of header");
Ray ray(0, 0, 3, 0, 2, true, r, v, false, fname, header);
ray.ite = 0;
ray.itr = 0;
ray.ine = 0;
ray.em.assign(3, -1.0);
ray.ab.assign(3, -2.0);
ray.sc.assign(3, -3.0);
ray.trace(g, m);

//  end trace_Mesh.inc
