/*=============================================================================
 
backlit_Ray.inc

#included in test_Ray.cpp

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 15 September 2015
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

double back_value(500.0);
Ray ray(0, 0, 1, 0, 0, false, Vector3d(), Vector3d(), false, "", "");
std::vector<double> hv;
hv.push_back(1000.0);
ray.set_backlighter(back_type, back_value, hv);

// end backlit_Ray.inc
