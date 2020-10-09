/**
 * @file diag_exec.inc
 * @brief Include file: for functions called from Diagnostics::execute()
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 22 December 2016\n
 * Last modified on 28 January 2020
 * @copyright (c) 2016, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

/*=============================================================================

#included in Diagnostics.cpp

Local variable setup common to the postprocessing and analysis modes in
functions Diagnostics::postprocess() and Diagnostics::analyze()

=============================================================================*/

// separators for Progress counters
const std::string DIAGSEP("****************************************\n");
const std::string DETSEP("========================================\n");

Grid g;
Mesh m;
Table tbl(h.get_table());
int ntd = h.get_ntd();
size_t ndet = size();

for (size_t id = 0; id < ndet; ++id)
{
    Detector &deti = det.at(id);
    deti.yst.fill(0.0);
    for (size_t itheta = 0; itheta < deti.get_ntheta(); ++itheta)
        for (size_t iphi = 0; iphi < deti.get_nphi(); ++iphi)
            deti.yt[IntPair(itheta, iphi)].fill(0.0);
}

size_t nintervals = h.get_nintervals();
size_t freq_det(freq == 0 ? 0 : 1);

//  end diag_exec.inc
