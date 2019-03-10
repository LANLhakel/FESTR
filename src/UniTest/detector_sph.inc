/*=============================================================================
 
detector_sph.inc

#included in test_Detector.cpp

pmh_2015_0312

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 7 March 2015
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

std::string dname("DetectorName");
std::string path("UniTest/Output/");
std::string dbpth("UniTest/Dbase1/");
std::string symmetry("spherical");
int my_id(7);
Vector3d rc(2.0, 0.0, 0.0);
Vector3d rx(0.0, 0.5, 0.0);
Vector3d ry(0.0, 0.0, 0.5);
double dx(0.2);
double dy(0.2);
size_t nhv(3);
double hv_min(300.0);
double hv_max(900.0);
double fwhm(-2.0); // no instrument broadening of spectra for fwhm <= 0
Vector3d sc(0.0, 0.0, 0.0);
std::string back_type("blackbody");
double back_value(7.0);
bool tracking(false);
Detector det(0, 0, 0, dname, path, dbpth, symmetry, my_id, rc, rx, ry,
             dx, dy, nhv, hv_min, hv_max, fwhm, sc, back_type, back_value,
             tracking);

// end detector_sph.inc
