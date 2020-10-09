/*=============================================================================
 
freq.inc

#included in test_Progress.cpp

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 13 August 2015
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

std::string name("get_freq");
std::string fname(cnststr::PATH + "UniTest/Output/" + name + ".txt");
#ifndef WIN
std::string cmnd("rm -rf " + fname);
if (system(cmnd.c_str()) != 0)
{
    std::cerr << "\nError: system call failure in freq.inc" << std::endl;
    exit(EXIT_FAILURE);
}
#endif
std::ofstream ostr(fname.c_str());
const int nlevel = 1;
const size_t freq_next = 3;
Progress counter(name, nlevel, n, freq, "", ostr);

//  end freq.inc
