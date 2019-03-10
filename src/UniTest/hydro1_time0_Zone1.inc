/*=============================================================================
 
hydro1_time0_Zone1.inc

#included in test_Zone.cpp, mix.inc

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 9 January 2015
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
std::string path(cnst::PATH + "/UniTest/Hydro1/");
std::string tlabel("0");
std::string fname = path + "time_" + tlabel + ".txt";
std::ifstream material(fname.c_str());
utils::find_word(material, "Zone");
utils::find_word(material, "Zone");
Zone z(1); // z.my_id will have been set on load from the "mesh" file
z.load_mat(material);
material.close();
material.clear();

// end hydro1_time0_Zone1.inc
