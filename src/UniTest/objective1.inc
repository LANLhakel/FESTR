/*=============================================================================
 
objective1.inc

#included in test_Objective.cpp

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 5 October 2015
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

Objective obj("ObjectiveNameXYW", cnststr::PATH + "UniTest/Goal1/",
              1, 2.0, true, true, false);
std::vector<double> a;
a.push_back(2.0);
a.push_back(1.0);
size_t n = a.size();
obj.update_best(a, n, 5); // better fitness found, this update will succeed

//  end objective1.inc
