/*=============================================================================
 
dbase3.inc

#included in test_Database.cpp, load_Table.inc, trace.inc

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 16 January 2015
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
std::string path(cnststr::PATH + "/UniTest/Dbase3/");
Database d("none", path, false);
double te(1000.0); // electron temperature -> 6400.0 in Dbase3
double tr(1000.0); // radiation temperature -> 0.0 in Dbase3
double np(1.0e16); // total particle number density (particles/cm3)
unsigned short int nmat(2); // number of materials
std::vector<std::string> mat; // material ID
mat.reserve(nmat);
mat.push_back("d");
mat.push_back("ar");
std::vector<double> fp; // fractional population of material
fp.reserve(nmat);
fp.push_back(0.6);
fp.push_back(0.4);
size_t ite(0); // te index initial guess
size_t itr(0); // tr index initial guess
size_t ine(0); // ne index initial guess
NeData ne_pair(d.find_ne(tbl, te, ite, tr, itr, np, nmat, mat, fp, ine));

//  end dbase3.inc
