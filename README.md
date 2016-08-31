# FESTR
Finite-Element Spectral Transfer of Radiation
Peter Hakel
Los Alamos National Laboratory
hakel@lanl.gov

Version 0.1 -- June 2015
Version 0.2 -- March 2016
Version 0.3 -- August 2016
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
