/*=============================================================================
 
rescale_y3.inc

#included in test_utilities.cpp

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 15 October 2015
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

const size_t n(3);

// original line positions
std::vector<double> hvold(n);
hvold[0] = 3.0;
hvold[1] = 5.0;
hvold[2] = 9.0;

// shifted line positions
std::vector<double> hvnew(n);
hvnew[0] = 1.5;
hvnew[1] = 4.5;
hvnew[2] = 9.5;

// scale factors at line positions
std::vector<double> sc(n);
sc[0] = 0.5;
sc[1] = 2.0;
sc[2] = 4.0;

const size_t m(7);

// data abscissas
std::vector<double> x(m);
x[0] = 2.0;
x[1] = 3.0;
x[2] = 4.0;
x[3] = 5.0;
x[4] = 8.0;
x[5] = 9.0;
x[6] = 9.5;

// data ordinates
std::vector<double> y(m);
y[0] = 8.0;
y[1] = 9.0;
y[2] = 5.0;
y[3] = 2.0;
y[4] = 5.0;
y[5] = 1.0;
y[6] = 6.5;

//  end rescale_y3.inc
