/*=============================================================================
 
set_bundle.inc

#included in test_Diagnostics.cpp

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 5 February 2015
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

double theta = det.get_theta_max();
size_t ntheta(10);
size_t nphi(360);
det.set_bundle(theta, ntheta, nphi);

// end set_bundle.inc
