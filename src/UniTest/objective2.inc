/*=============================================================================
 
objective2.inc

#included in test_Objective.cpp

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 5 October 2015
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

#include "objective1.inc"
a.at(0) = 2000.0;
a.at(1) = 1000.0;
obj.update_best(a, n, 6); // previous fitness is better, this update will fail

// end objective2.inc
