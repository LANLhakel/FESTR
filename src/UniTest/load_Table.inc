/*=============================================================================
 
load_Table.inc

#included in dbase3.inc, hydro1_time0_Zone1.inc,
             trace_Mesh.inc, trace_conic_Mesh.inc

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 18 July 2015
Last modified on 28 January 2020

Copyright (c) 2015, Triad National Security, LLC.
All rights reserved.
Use of this source code is governed by the BSD 3-Clause License.
See top-level license.txt file for full license text.

CODE NAME:  FESTR, Version 0.8 (C15068)
Classification Review Number: LA-CC-15-045
Export Control Classification Number (ECCN): EAR99
B&R Code:  DP1516090

=============================================================================*/

std::string hydro_path(cnststr::PATH + "UniTest/Data/");
std::string table_path(cnststr::PATH + "UniTest/Data/");
std::string table_fname("Table.txt");
Table tbl(hydro_path, table_path, table_fname);

//  end load_Table.inc
