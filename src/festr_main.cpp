/**
 * @file
 * @brief FESTR driver, usage: ./festr \<options_file\>
 * @author Peter Hakel
 * @version 0.9
 * @date Created on 23 October 2014\n
 * Last modified on 6 October 2020
 * @copyright (c) 2015, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

/*=============================================================================

Finite-Element Spectral Transfer of Radiation

festr.cpp

CODE NAME:  FESTR, Version 0.9 (C15068)
Classification Review Number: LA-CC-15-045
Export Control Classification Number (ECCN): EAR99
B&R Code:  DP1516090

=============================================================================*/

#include <Diagnostics.h>
#include <Goal.h>
#include <Hydro.h>
#include <utils.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

#ifdef MPI
#include <mpi.h>
#endif

//-----------------------------------------------------------------------------

/** @brief Name of this code */
const std::string main_name = "festr";

//-----------------------------------------------------------------------------

/** @brief Prints the format of the execution command */
void print_usage()
{
    std::cout << "Usage: ./" << main_name << " <options_file>" << std::endl;
}

//-----------------------------------------------------------------------------

/** @brief Main driver of this code */
int main(int argc, char **argv)
{
    const int level = 0; // indentation level for local Progress objects

std::string license("Copyright (c) 2015, Triad National Security, LLC");
license += "\nAll rights reserved.\n\n";
license += "Copyright 2015. Triad National Security, LLC.\n";
license += "This program was produced under U.S. Government contract\n";
license += "89233218CNA000001 for Los Alamos National Laboratory (LANL), which is\n";
license += "operated by Triad National Security, LLC for the U.S. Department\n";
license += "of Energy/National Nuclear Security Administration.\n\n";
license += "All rights in the program are reserved by Triad National Security, LLC,\n";
license += "and the U.S. Department of Energy/National Nuclear Security Administration.\n";
license += "The Government is granted for itself and others acting on its behalf\n";
license += "a nonexclusive, paid-up, irrevocable worldwide license in this material\n";
license += "to reproduce, prepare derivative works, distribute copies to the public,\n";
license += "perform publicly and display publicly, and to permit others to do so.\n\n";
license += "The U.S. Government has rights to use, reproduce, and\n";
license += "distribute this software. NEITHER THE GOVERNMENT NOR TRIAD\n";
license += "NATIONAL SECURITY, LLC MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR\n";
license += "ASSUMES ANY LIABILITY FOR THE USE OF THIS SOFTWARE. If software is\n";
license += "modified to produce derivative works, such modified software should be\n";
license += "clearly marked, so as not to confuse it with the version available from\n";
license += "LANL.\n\n";
license += "Additionally, redistribution and use in source and binary forms, with\n";
license += "or without modification, are permitted provided that the following\n";
license += "conditions are met:\n\n";
license += "1. Redistributions of source code must retain the above copyright\n";
license += "   notice, this list of conditions and the following disclaimer.\n\n";
license += "2. Redistributions in binary form must reproduce the above\n";
license += "   copyright notice, this list of conditions and the following\n";
license += "   disclaimer in the documentation and/or other materials provided\n";
license += "   with the distribution.\n\n";
license += "3. Neither the name of Triad National Security, LLC, Los Alamos\n";
license += "   National Laboratory, LANL, the U.S. Government, nor the names of its\n";
license += "   contributors may be used to endorse or promote products derived from\n";
license += "   this software without specific prior written permission.\n\n";
license += "THIS SOFTWARE IS PROVIDED BY TRIAD NATIONAL SECURITY, LLC AND\n";
license += "CONTRIBUTORS \"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,\n";
license += "BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS\n";
license += "FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TRIAD\n";
license += "NATIONAL SECURITY, LLC OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,\n";
license += "INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES\n";
license += "(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR\n";
license += "SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)\n";
license += "HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,\n";
license += "STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING\n";
license += "IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE\n";
license += "POSSIBILITY OF SUCH DAMAGE.\n";

    std::cout << license
              << "\nFESTR: Finite-Element Spectral Transfer of Radiation, "
              << "Version 0.9, October 2020\n" << std::endl;

    if (argc != 2)
    {
        print_usage();
        exit(EXIT_FAILURE);
    }
    std::cout << "Running: ";
    for (int i = 0; i < argc; ++i) std::cout << " " << argv[i];
    std::cout << "\n" << std::endl;

    std::ifstream options(argv[1]);
    if (!options.is_open())
    {
        std::cerr << "Error: file " << argv[1] << " is not open "
                  << "in festr::main" << std::endl;
        print_usage();
        exit(EXIT_FAILURE);
    }

    utils::find_word(options, "Top_path:");
    std::string top_path;
    options >> top_path;
    std::cout << "Top path: " << top_path << std::endl;

    utils::find_word(options, "Goal:");
    std::string goal_path;
    options >> goal_path;
    bool analysis(goal_path != "none");
    std::cout << "\nGoal path: " << goal_path << std::endl;
    goal_path = top_path + goal_path;
    std::cout << "... loading Goal ... " << std::flush;
    Goal gol(analysis, goal_path);
    std::cout << "done" << std::endl;

    utils::find_word(options, "Output:");
    std::string out_path;
    options >> out_path;
    std::cout << "\nOutput data path: " << out_path << std::endl;
    out_path = top_path + out_path;

    utils::find_word(options, "Material_table_path:");
    std::string table_path;
    options >> table_path;
    std::cout << "\nMaterial table path: " << table_path << std::endl;
    table_path = top_path + table_path;
    utils::find_word(options, "Material_table_file_name:");
    std::string table_fname;
    options >> table_fname;
    std::cout << "\nMaterial table file name: " << table_fname << std::endl;

    utils::find_word(options, "Hydro:");
    std::string hydro_path;
    options >> hydro_path;
    std::cout << "\nHydro path: " << hydro_path << std::endl;
    hydro_path = top_path + hydro_path;

    utils::find_word(options, "TOPS_command:");
    std::string tops_cmnd;
    options >> tops_cmnd;
    std::cout << "\nTOPS command: " << tops_cmnd << std::endl;
    utils::find_word(options, "Database:");
    std::string dbase_path;
    options >> dbase_path;
    std::cout << "\nEOS/optical Database path: " << dbase_path << std::endl;
    bool tops_default(dbase_path == "tops_default/");
    dbase_path = top_path + dbase_path;
    std::cout << "... loading Database ... " << std::flush;
    Database d(tops_cmnd, dbase_path, tops_default);
    std::cout << "done" << std::endl;

    utils::find_word(options, "Diagnostics:");
    std::string diag_path;
    options >> diag_path;
    std::cout << "\nDiagnostics path: " << diag_path << std::endl;
    diag_path = top_path + diag_path;
    std::cout << "... loading Diagnostics ... " << std::flush;
    Diagnostics diag(level+1, diag_path, hydro_path, out_path, d);
    std::cout << "done" << std::endl;

    // limit the time range for postprocessing
    double tmin = 1.0e99;
    double tmax = -1.0e99;
    if (!analysis)
    {
        utils::find_word(options, "tmin_tmax:");
        options >> tmin >> tmax;
        std::cout << "\ntmin_tmax: " << tmin << " " << tmax << " seconds"
                  << std::endl;
    }

    // split from reading hydro_path, because Diagnostics needs hydro_path,
    // but then Hydro constructor needs Detector symmetry (via Diagnostics)
    std::cout << "\n... loading Hydro ... " << std::flush;
    Hydro h(analysis, hydro_path, table_path, table_fname,
            diag.det.at(0).get_symmetry(), tmin, tmax);
    std::cout << "done" << std::endl;

    std::cout << "\n... festr is running ...\n" << std::endl;
    #ifdef MPI
    MPI_Init(&argc, &argv);
    #endif
    diag.execute(d, h, gol);
    #ifdef MPI
    MPI_Finalize();
    #endif
    std::cout << "\nend" << std::endl;

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------

// end festr_main.cpp
