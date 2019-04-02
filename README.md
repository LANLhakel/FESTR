# FESTR
Finite-Element Spectral Transfer of Radiation
Peter Hakel
Los Alamos National Laboratory
hakel@lanl.gov

Version 0.1 -- June 2015

Version 0.2 -- March 2016

Version 0.3 -- August 2016

Version 0.4 -- October 2016

Version 0.5 -- August 2017

Version 0.6 -- April 2018

Version 0.7 -- November 2018

Version 0.8 -- March 2019

CODE NAME:  FESTR (C15068)

Classification Review Number: LA-CC-15-045

Export Control Classification Number (ECCN): EAR99

B&R Code:  DP1516090

Description:

FESTR is a modeling tool for calculating spectroscopic-quality synthetic
outputs (e.g., spectra and images) based on (in general) the time evolutions
of 3-D spatial distributions of materials characterized by their chemical
composition, temperature, and density conditions. FESTR performs raytracing
across unstructured meshes, builds intrinsic optical properties of mixed
materials by performing equation-of-state lookups in external data, and then
solves the radiation-transport equation along rays to obtain emergent time and
space resolved synthetic spectra. These results can be further processed into
time and/or space integrated spectra, as well as into spectral-band-integrated
synthetic images, radiated power histories, and total radiated energy values.
FESTR is also applicable to spatial reconstructions of material properties via
the analysis of experimental data.

Publications:

Peter Hakel,
"FESTR: Finite-Element Spectral Transfer of Radiation spectroscopic modeling
 and analysis code",
Computer Physics Communications, vol. 207, pp. 415-425 (2016). (open access)

http://dx.doi.org/10.1016/j.cpc.2016.05.027

Directory structure:

common: resources that could be reused in other projects (makefile,
        the unit test mechanism, MPI parallelization)

doc: documentation of this package

img: utilities for preparing synthetic images based on FESTR output

src: source files for this package

src/build: target directory for object files produced during compilation

src/Histories: postprocessor to generate time histories of outputs

src/ObjPrep: preprocessor to create inputs for the analysis mode
             (fixed weights)

src/ObjPrepErrorBars: preprocessor to create inputs for the analysis mode
                      (variable weights)

src/Plot: utility to process output spectra for plotting

src/Sample: input/output data for a sample FESTR run

src/Scale: utility to rescale, shift, and calibrate experimental spectra

src/src: FESTR source files

src/UniTest: source files for FESTR unit tests

===============================================================================


Version Log:

-------------------------------------------------------------------------------

0.1, June 2015

     Initial release:

     *) EOS and optical data lookups in pure-element databases (with
        ionization) and their mixing according to the chemical composition,

     *) 3-D raytracing across unstructured meshes
        (Face = Sphere, Cone, Polygon, Surface have been implemented),

     *) solution of the steady-state radiation-transport equation along Rays
        and calculation of space/time resolved/integrated spectra,

     *) Detectors using parallel Rays (infinite focus) coded and tested,

     *) non-parallel Rays (parallax effects) also coded, but not tested yet,

     *) tools for creating synthetic 2-D spectral-band-integrated images,

     *) a simple but general native unit test framework (class Test).

-------------------------------------------------------------------------------

0.2, March 2016

     Release: festr_v0.2.tgz, added:

     *) Doxygen documentation of the source code, accessible via file:
        doc/html/index.html to be viewed with a web browser,

     *) classes Objective, Goal in support of the analysis mode,

     *) class Progress for monitoring of progress of the calculation.

-------------------------------------------------------------------------------

0.3, August 2016

     Release: festr_v0.3.tgz, added:

     *) bug fix in Detector::patch_string, where a missing (symmetry != “none”)
        branch was added;
        added two new associated unit tests in test_Detector.cpp:
        Detector_patch_string_symmetry_none,
        Detector_patch_string_symmetry_spherical;
        adjusted “expected” values in two existing unit tests in
        test_Diagnostics.cpp also affected by the above described change:
        Diagnostics_do_history_SphSym1d_symmetry_spherical_center_patch
        Diagnostics_do_history_SphSym1d_flat_backlighter_center_patch

     *) bug fix in Zone::load_mat, to ensure correct function in analysis mode

-------------------------------------------------------------------------------

0.4, October 2016

     Release: festr_v0.4.tgz, added:

     *) bug fix in Detector::do_Ray, where the wrong use of the “patch”
        variable in the “spherical cap” if-test was changed to use the
        correct “direction” variable;

     *) a hard zero was replaced with 1.0e-19 in Cone::contains in order to
        avoid spurious rejection of a valid solution due to round-off errors
        for Rays exactly following the z-axis; three new unit tests (with names
        containing "Ray_on_axis") were added to file test_Cone.cpp to cover
        this edge case.

-------------------------------------------------------------------------------

0.5, August 2017

     Release: festr_v0.5.tgz:

     *) Diagnostics constructor was extended to copy the times.txt input file
        from the Hydro directory into the Output directories of all Detectors
        in order to support postprocessing utilities time_hist and time_intavg,
        unit test Diagnostics_Detector0_times_file_copy was added,

     *) files Sphere1d-yp_time0_img.dat, Sphere1d-yp_time0_img.png,
        c_car_img, car_img.cpp were added in directory img/ to enable the
        generation of synthetic images from generic space-resolved spectra
        (i.e., from spectra whose Detector has symmetry = none),

     *) the meaning of the third argument in functions nearest and
        nearest_exh (file utilities.h) has been changed in order to allow the
        optimization of the subsequent loop in nearest_exh, calls to these
        functions were updated accordingly, two new tests (utilities_nearest0
        and utilities_nearest_exh_empty) were added to cover edge cases,

     *) function Diagnostics::do_history() was renamed execute(),
        refactored, and split into two shorter functions:
        Diagnostics::postprocess() and Diagnostics::analyze(),
        file do_history.cpp was renamed diag_exec.cpp,
        replacements of "do_history" with "execute" were carried out in the
        file Test/test_Diagnostics.cpp,

     *) code in function Diagnostics::postprocess() was refactored to
        accomodate MPI-parallelization of time steps using class TaskPool,

     *) code in function Detector::yt_to_files() was refactored to accomodate
        MPI-parallelization of time integration using class ReducePool,
        a new function Detector::yst_using_mpi() was added in a similar manner,

     *) OpenMP threading directives were added to ArrDblLoop.cpp and
        Objective.h,

     *) several methods in class ArrDbl were found to be thread-unsafe and
        corrected accordingly,

     *) makefile was enhanced with additional variables controlling the level
        of optimization (opt), OpenMP threading (omp), and MPI parallelization
        (mpi),

     *) for completeness, "np" fields were added for each Zone in the file
        Test/Analysis1/time_0.txt,

     *) NOTE: the unit tests are not designed to run with MPI parallelization.

-------------------------------------------------------------------------------

0.6, April 2018

     Release: festr_v0.6.tgz:

     *) The src/Sample/Data/Table.txt file content was updated to handle
        element symbols starting with an uppercase letter,

     *) Portland compiler name was changed from pgcpp to pgc++ in the makefile,

     *) unit test names now use hyphen (instead of the original underscore) to
        mark the end of the tests' group names (change in Test::get_id),

     *) function replace_in_string was added in utilities, new related unit
        tests were also added,

     *) function string_to_bool (in utilities) was extended to accept "yes"
        and "no" inputs,

     *) new "tracking" members were added to classes Detector and Ray to mark
        whether partial spectral results (along the specified Rays) should also
        be output (the default is "no" i.e., "false"), several unit tests were
        added and modified accordingly,

     *) new members "nzd", "iz", "distance", "froot", and "hroot" were added
        in class Ray to support the newly added "tracking" capability of
        partial spectral results along a Ray, functions Detector::do_Ray,
        Detector::omega_string, Ray::trace, and Ray_cross_Zone were modified
        to support this new capability,

     *) additional argument "nzmesh" was added to function Ray::cross_Zone,

     *) Database constructor was modified to allow the reading of photon-energy
        grids made of doubles (instead of the original integers),

     *) Detector constructor was modified to print an error message and halt
        the program, if the Detector's photon-energy range is entirely outside
        of the photon-energy range of the Database,

     *) Database constructor was given a third argument (type bool) to flag
        whether the database path was set to "tops_default/" or not,
        a getter function for this new member of class Database was added, all
        affected unit tests were updated with this value set to "false" and
        the festr.cpp file was changed accordingly.

-------------------------------------------------------------------------------

0.7, November 2018

     Release: festr_v0.7.tgz:

     *) The makefile was generalized to use wildcard functionality and
        placed into the new directory named "common" along with MPI and
        unit-test relevant source files,

     *) the source file containing the "main" function was renamed
        "festr_main.cpp" and all the other production source files were moved
        to the new "src" subdirectory (within the old "src"),

     *) the Doxygen documentation (located in directory "doc/html") now
        captures entities declared and defined in this new "src/src"
        subdirectory (i.e., "main" and "common" files are no longer included),

     *) object files are now assembled into library ("*.a") archive files
        before linking with the object file containing the "main" function;
        this change should facilitate the reuse of FESTR functions in other
        possible future projects,

     *) new "log" rule added to the makefile creates the file named
        "makelog.txt" containing the configuration of the latest
        "make libfestr.a" build; this new file therefore contains a record
        of the build choices made for "libfestr.a" for future reference,

     *) entities from "utilities" are now encapsulated in the namespace
        "utils"; entities from "constants" are now encapsulated in the
        namespace "cnst"; all source code was updated accordingly,

     *) the filename extensions of include files were changed from ".cpp"
        to ".inc",

     *) subdirectory "Test" was renamed "UniTest", and two new files
        named "tests_headers.inc" and "tests_runs.inc" were created by
        cutting FESTR-specific code out of "tests.cpp" (now located in the
        "common/UniTest" directory),

     *) the new file "test_Face.cpp" containing an empty function was created
        per the demands of the updated (and more automated) makefile,

     *) compilation scripts and source code for supporting programs were
        modified to accommodate the changes described above.

-------------------------------------------------------------------------------

0.8, March 2019

     Release of version 0.8:

     *) The copyright notice was changed to reflect the transition of the
        Los Alamos National Laboratory M&O contract from Los Alamos National
        Security, LLC, to Triad National Security, LLC,

     *) In class ArrDbl return types were changed to references for all
        compound assignments, const was added to return types of unary and
        binary operators, four unit tests covering compound assignments with
        self were added in file test_ArrDbl.cpp,

     *) file "img/img.py" was converted to Python 3 and made self-executable,

     *) "build" subdirectory was created to store object files during the
        compilation; the makefile was changed accordingly.

-------------------------------------------------------------------------------

