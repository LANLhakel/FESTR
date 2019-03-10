/*=============================================================================
 
diagnostics4.inc

#included in test_Diagnostics.cpp
Like diagnostics3.cpp, but using a flat, non-zero backlighter_value = 3.00e+30

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
transmission = exp(-op*chord_length)
self_emission = em / op * (1 - transmission)
Test Diagnostics_do_history_SphSym1d_flat_backlighter_center_patch:
yp(thin)         = backlighter_value  +  em * chord_length = 7.060000e+30
yp(intermediate) = backlighter_value * transmission  +  self_emission
                 = 7.476306e+30
yp(thick) = 3.00e+30 * exp(-6.644e0) + 2.03e+31 / 6.644e+0 * (1-exp(-6.644e0))
          = 3.051411e+30

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 16 September 2015
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

std::string hydro_path(cnst::PATH + "UniTest/Hydro3/");
std::string table_path(cnst::PATH + "UniTest/Data/");
std::string table_fname("Table.txt");
std::string symmetry("spherical");
Goal gol;
Hydro h(false, hydro_path, table_path, table_fname, symmetry);
size_t it(1);
std::string tlabel(utils::int_to_string(it, '0', h.get_ntd()));
Grid g(hydro_path, tlabel);
Mesh m(hydro_path, tlabel);
Database d("none", cnst::PATH + "UniTest/Dbase3/", false);
Diagnostics diag(0, cnst::PATH + "UniTest/Diagnostics4/", hydro_path, cnst::PATH, d);
Detector &det = diag.det.at(0);

// end diagnostics4.inc
