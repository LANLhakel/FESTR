/*=============================================================================
 
mix.inc

#included in test_Zone.cpp

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 24 January 2015
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

#include <hydro1_time0_Zone1.inc>
Database d("none", cnststr::PATH + "/UniTest/Dbase3/", false);
double te = z.get_te();
size_t ite(0);
double tr = z.get_tr();
size_t itr(0);
double np = z.get_np();
size_t ine(0);
unsigned short int nmat = z.get_nmat();
const std::vector<std::string> & mat = z.get_mat();
const std::vector<double> & fp = z.get_fp();
std::pair<double, std::string> ne_pair;
ne_pair = d.find_ne(tbl, te, ite, tr, itr, np, nmat, mat, fp, ine);
size_t nhv = d.get_nhv();
ArrDbl em(nhv), ab(nhv), sc(nhv);
z.load_spectra(d, tbl, ite, itr, ine, "none", 0, false, 0, 2, em, ab, sc);

//  end mix.inc
