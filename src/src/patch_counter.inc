/**
 * @file patch_counter.inc
 * @brief Include file: sets up Progress object for monitoring Detector patches
 * @author Peter Hakel
 * @version 0.8
 * @date Created on 29 January 2016\n
 * Last modified on 13 March 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */


/*=============================================================================

#included in Detector.cpp

=============================================================================*/

int next_level;
size_t next_freq;
if (parent == nullptr)
{
    next_level = 0;
    next_freq = 0;
}
else
{
    next_level = parent->get_level() + 1;
    next_freq = parent->get_next_freq(freq_patch);
}
const std::string SEP("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
Progress counter(dname + "_patch", next_level, nx*ny, next_freq,
                 SEP, std::cout);

//  end patch_counter.inc
