/*=============================================================================
 
diagnostics2.inc

#included in test_Diagnostics.cpp

pmh_2015_0312

Space-integrated uniform sphere emergent intensity expressions were taken from
Burris-Mog et al., JQSRT 99, 120 (2006).

yp = patch spectrum (space and time resolved)
Emissivities and opacities as in test_Zone.cpp, from
Tests Zone_load_Hydro1_Time0_Zone1_??? (optically thin, intermediate, thick):
em = 4.06e+30, 8.12e+30, 2.03e+31
ab = 6.04e-5, 6.04e-1, 6.04e+0
sc = 6.04e-6, 6.04e-2, 6.04e-1
op = ab + sc = 6.644e-5, 6.644e-1, 6.644e0
chord_length = sphere_diameter = 1 cm
Test Diagnostics_do_history_Sphere1d_Cartesian_center_patch:
yp(thin)         = em * chord_length = 4.060000e+30
yp(intermediate) = em / op * (1 - exp(-op*chord_length)) = 5.932560e+30
yp(thick)        = 2.03e+31 / 6.644e+0 * (1 - exp(-6.644e0)) = 3.051411e+30

ys = space integrated, time resolved spectrum
Test Diagnostics_do_history_Sphere1d_symmetry_none_time0_ys:
Diagnostics2 spatial resolution of 0.2 cm is in the ballpark of recovering
the exact space-integrated spectral values for the optically
thin:         2.264222e+30 (Eq. 3: 2.126537e+30 ~ Eq. 4)
intermediate: 3.602169e+30 (Eq. 3: 3.356725e+30)
thick:        2.504046e+30 (Eq. 3: 2.292054e+30 ~ Eq. 5)
cases, but better resolution increases time and disk space requirements.

yst = space and time integrated spectrum
Test Diagnostics_do_history_Sphere1d_symmetry_none_yst:
time_interval = 7e-9 s
yst = ys * time_interval (material defined as constant during time_interval)
yst(thin)         = 2.264222e+30 * 7e-9 = 1.584955e+22
yst(intermediate) = 3.602169e+30 * 7e-9 = 2.521518e+22
yst(thick)        = 2.504046e+30 * 7e-9 = 1.752832e+22

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 4 March 2015
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

std::string hydro_path(cnststr::PATH + "UniTest/Hydro3/");
std::string table_path(cnststr::PATH + "UniTest/Data/");
std::string table_fname("Table.txt");
std::string symmetry("none");
Goal gol;
Hydro h(false, hydro_path, table_path, table_fname, symmetry, -1.0, 1.0);
size_t it(1);
std::string tlabel(utils::int_to_string(it, '0', h.get_ntd()));
Grid g(hydro_path, tlabel);
Mesh m(hydro_path, tlabel);
Database d("none", cnststr::PATH + "UniTest/Dbase3/", false);
Diagnostics diag(0, cnststr::PATH + "UniTest/Diagnostics2/", hydro_path, cnststr::PATH, d);
Detector &det = diag.det.at(0);

//  end diagnostics2.inc
