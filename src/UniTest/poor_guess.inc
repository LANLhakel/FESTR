/*=============================================================================
 
poor_guess.inc

#included in test_Goal.cpp

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 14 July 2015
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

#include <goal1.inc>
a.fill(1000.0);
gol.fit_eval("ObjectiveNameXYW", a);
gol.fit_eval("ObjectiveNameYW", a);
gol.fit_eval("ObjectiveNameXY", a);
gol.fit_eval("ObjectiveNameY", a);
gol.update_best(23);

//  end poor_guess.inc
