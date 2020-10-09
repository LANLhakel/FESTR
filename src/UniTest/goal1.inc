/*=============================================================================
 
goal1.inc

#included in test_Goal.cpp, poor_guess.inc

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 14 July 2015
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

Goal gol(true, cnststr::PATH + "UniTest/Goal1/");
ArrDbl a(2);
a.fill(0.0);
gol.fit_eval("ObjectiveNameXYW", a);
a.fill(1.0);
gol.fit_eval("ObjectiveNameYW", a);
a.fill(2.0);
gol.fit_eval("ObjectiveNameXY", a);
a.fill(3.0);
gol.fit_eval("ObjectiveNameY", a);
gol.update_best(11);

//  end goal1.inc
