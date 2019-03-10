/**
 * @file choose_root.inc
 * @brief Include file: quadratic equation solution
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 19 May 2015\n
 * Last modified on 3 March 2019
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

/*=============================================================================

#included in Sphere.cpp, Cone.cpp (method intercept)

Choose the smallest positive root given by a quadratic equation
and return the corresponding point along a straight line.

=============================================================================*/

const utils::RetQuad x = utils::solve_quadratic(a, b, c, eqt);
// x.x2 <= x.x1 is guaranteed by solve_quadratic()

if (x.nroots == 0) // Ray does not intersect Face
{
    const double BIG = -Vector3d::get_big();
    rv.t = BIG;
    rv.w = Vector3d(BIG, BIG, BIG);
    rv.is_found = false;
    return rv; // no solution
}

// see Zone::hit() about the choice for the EQT value
rv.is_found = utils::sign_eqt(x.x1, eqt) == 1; // if x.x1 > 0, we have
// a possible solution, but which one of the two roots should we return?
// look for the smallest positive solution "contained" by *this Face

// test x.x1 root
rv.t = x.x1;
bool is_contained_1(contains(g, p + u*x.x1)  &&  rv.is_found);
bool is_contained(is_contained_1);

// test x.x2 root
bool is_contained_2(contains(g, p + u*x.x2)  &&  rv.is_found);
if (rv.fid != fid  &&  rv.is_found  &&
    utils::sign_eqt(x.x2, eqt) == 1  &&  is_contained_2)
{
    rv.t = x.x2; // 0 < x.x2 <= x.x1
    is_contained = is_contained_2;
}

rv.w = p  +  u * rv.t;
rv.is_found &= is_contained;

return rv;

// end choose_root.inc
