/*=============================================================================
 
transport_Ray.inc

#included in test_Ray.cpp

Peter Hakel
Los Alamos National Laboratory
XCP-5 group

Created on 27 January 2015
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

Ray ray(0, 0, 3, 0, 2, false, Vector3d(), Vector3d(), false, "", "");
ray.y.fill(20.0);
ray.em.fill(300.0);
ray.ab.at(0) = 1.0e-11;
ray.ab.at(1) = 1.0e0;
ray.ab.at(2) = 1.0e1;
ray.sc.at(0) = 2.0e-11;
ray.sc.at(1) = 2.0e0;
ray.sc.at(2) = 2.0e1;
double ct = 0.4;
ray.transport(ct);

//  end transport_Ray.inc
