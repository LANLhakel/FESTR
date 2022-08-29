/*=============================================================================
 
diagnostics_solid_angle_at20cm.inc

#included in test_Diagnostics.cpp
Materials chosen to be optically thick with source function = 1

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 8 August 2022
Last modified on 11 August 2022

Copyright (c) 2015, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

CODE NAME:  FESTR, Version 0.9 (C15068)
Classification Review Number: LA-CC-15-045
Export Control Classification Number (ECCN): EAR99
B&R Code:  DP1516090

=============================================================================*/

#ifdef _OPENMP
glob::nthreads = 36;
#endif

std::string hydro_path(cnststr::PATH + "UniTest/Hydro_solid_angle/");
std::string table_path(cnststr::PATH + "UniTest/Data/");
std::string table_fname("Table.txt");
std::string symmetry("none");
Goal gol;
Hydro h(false, hydro_path, table_path, table_fname, symmetry, -1.0, 1.0);
size_t it(1);
std::string tlabel(utils::int_to_string(it, '0', h.get_ntd()));
Grid g(hydro_path, tlabel);
Mesh m(hydro_path, tlabel);
Database d("none", cnststr::PATH + "UniTest/Dbase_solid_angle/", false);
Diagnostics diag(0, cnststr::PATH + "UniTest/Diagnostics_solid_angle_at20cm/", hydro_path, cnststr::PATH, d);
Detector &det = diag.det.at(0);

//  end diagnostics_solid_angle_at20cm.inc
