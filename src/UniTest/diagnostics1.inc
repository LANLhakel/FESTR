/*=============================================================================
 
diagnostics1.inc

#included in test_Diagnostics.cpp

pmh_2015_0210

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 11 February 2015
Last modified on 28 January 2020

Copyright (c) 2015, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

CODE NAME:  FESTR, Version 0.9 (C15068)
Classification Review Number: LA-CC-15-045
Export Control Classification Number (ECCN): EAR99
B&R Code:  DP1516090

=============================================================================*/

std::string hydro_path(cnststr::PATH + "UniTest/Hydro2/");
std::string table_path(cnststr::PATH + "UniTest/Data/");
std::string table_fname("Table.txt");
std::string symmetry("none");
Table tbl(hydro_path, table_path, table_fname);
Hydro h(false, hydro_path, table_path, table_fname, symmetry, -1.0, 1.0);
size_t it(1);
std::string tlabel(utils::int_to_string(it, '0', h.get_ntd()));
Grid g(hydro_path, tlabel);
Mesh m(hydro_path, tlabel);
Database d("none", cnststr::PATH + "UniTest/Dbase3/", false);
Diagnostics diag(0, cnststr::PATH + "UniTest/Diagnostics1/", hydro_path, cnststr::PATH, d);
Detector &det = diag.det.at(0);

//  end diagnostics1.inc
