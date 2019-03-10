/*=============================================================================
 
trace_conic_Mesh.inc

#included in test_Ray.cpp

pmh_2015_0522

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 22 May 2015
Last modified on 3 March 2019

Copyright (c) 2015, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

CODE NAME:  FESTR, Version 0.8 (C15068)
Classification Review Number: LA-CC-15-045
Export Control Classification Number (ECCN): EAR99
B&R Code:  DP1516090

=============================================================================*/

#include "load_Table.inc"
std::string path(cnst::PATH + "UniTest/Hydro4/");
std::string tlabel("0");
Grid g(path, tlabel);
Mesh m(path, tlabel);
Database d("none", cnst::PATH + "UniTest/Dbase3/", false);
Vector3d r(-20.6592869168006, -31.488930375200901, -92.637147667202399);
Vector3d v(2.0, 3.0, 8.0);
Ray ray(0, 0, 3, 0, 2, false, r, v, false, "", "");
ray.ite = 0;
ray.itr = 0;
ray.ine = 0;
ray.em.assign(3, -1.0);
ray.ab.assign(3, -2.0);
ray.sc.assign(3, -3.0);
ray.trace(g, m);

// end trace_conic_Mesh.inc
