/*=============================================================================
 
progress.cpp

#included in test_Progress.cpp

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 11 August 2015
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

std::string fname(cnst::PATH + "UniTest/Output/" + name + ".txt");
std::string cmnd("rm -rf " + fname);

if (system(cmnd.c_str()) != 0)
{
    std::cerr << "\nError: system call failure in progress.inc" << std::endl;
    exit(EXIT_FAILURE);
}

std::ofstream ostr(fname.c_str());
{
    Progress counter(name, nlevel, n, freq, "", ostr);
    for (size_t i = 0; i < ncount; ++i) counter.advance();
}
ostr.close();
ostr.clear();

std::string label("");
for (int k = 0; k < nlevel; ++k) label += ">";
label += " " + name + ": ";
std::string expected("");

// end progress.inc
