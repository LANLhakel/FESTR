/*=============================================================================
 
hydro1.inc

#included in test_Hydro.cpp

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 11 July 2015
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

std::string hydro_path(cnst::PATH + "UniTest/Hydro1/");
std::string table_path(cnst::PATH + "UniTest/Data/");
std::string table_fname("Table.txt");
Hydro h(false, hydro_path, table_path, table_fname, "none");

// end hydro1.inc
