/*=============================================================================
 
analysis1.inc

#included in test_Cell.cpp

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 4 July 2015
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

std::string fname(cnststr::PATH + "UniTest/Analysis1/time_0.txt");
std::ifstream material(fname.c_str());
if (!material.is_open())
{
    std::cerr << "Error: file " << fname << " is not open." << std::endl;
    exit(EXIT_FAILURE);
}

Cell z0(material);
Cell z1(material);

//  end analysis1.inc
