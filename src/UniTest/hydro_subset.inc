/*=============================================================================
 
hydro_subset.inc

#included in test_Hydro.cpp

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 20 November 2019
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

std::string hydro_path(cnststr::PATH + "UniTest/Hydro_subset/");
std::string table_path(cnststr::PATH + "UniTest/Data/");
std::string table_fname("Table.txt");
Hydro h(false, hydro_path, table_path, table_fname, "none", 3.5, 7.5);

//  end hydro_subset.inc
